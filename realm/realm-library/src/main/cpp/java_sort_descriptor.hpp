/*
 * Copyright 2016 Realm Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef JAVA_SORT_DESCRIPTOR_HPP
#define JAVA_SORT_DESCRIPTOR_HPP

#include <jni.h>
#include <realm/views.hpp>

namespace realm {
namespace _impl {

// For converting a Java SortDescriptor object to realm::SortDescriptor.
// This class is not designed to be used across JNI calls. So it doesn't acquire a reference to the given Java object.
// We don't hold a pointer to the SortDescriptor in the Java object like normally we do, because the ObjectStore
// always consumes the SortDescriptor by calling the move constructor. Holding an empty SortDescriptor in Java level
// doesn't make too much sense and causes troubles with memory management.
class JavaSortDescriptor {
public:
    JavaSortDescriptor(JNIEnv* env, jobject sort_desc_obj)
        : m_env(env)
        , m_sort_desc_obj(sort_desc_obj)
    {
    }

    JavaSortDescriptor(const JavaSortDescriptor&) = delete;
    JavaSortDescriptor& operator=(const JavaSortDescriptor&) = delete;
    JavaSortDescriptor(JavaSortDescriptor&&) = delete;
    JavaSortDescriptor& operator=(JavaSortDescriptor&&) = delete;

    operator realm::SortDescriptor() const noexcept;

private:
    JNIEnv* m_env;
    jobject m_sort_desc_obj;
};

} // namespace _impl
} // namespace realm
#endif // JAVA_SORT_DESCRIPTOR_HPP
