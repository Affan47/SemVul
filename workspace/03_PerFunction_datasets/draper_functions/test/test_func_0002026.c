JNI_GetObjectArrayElement(JNIEnv *env, jobjectArray array, jsize index)
{
	enter_vm_from_jni();

	if (array == NULL) {
		signal_new_exception(vm_java_lang_NullPointerException, NULL);
		return NULL;
	}
	if (index >= vm_array_length(array)) {
		signal_new_exception(vm_java_lang_ArrayIndexOutOfBoundsException, NULL);
		return NULL;
	}

	return array_get_field_object(array, index);
}
