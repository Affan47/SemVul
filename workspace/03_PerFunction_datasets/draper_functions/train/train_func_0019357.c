JNI_GetStringUTFChars(JNIEnv *env, jstring string, jboolean *isCopy)
{
	jbyte *array;

	enter_vm_from_jni();

	if (!string)
		return NULL;

	array = (jbyte *) vm_string_to_cstr(string);
	if (!array)
		return NULL;

	if (isCopy)
		*isCopy = true;


	return (char*) array;
}
