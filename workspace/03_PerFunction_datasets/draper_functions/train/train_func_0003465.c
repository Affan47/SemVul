JNI_ReleaseStringUTFChars(JNIEnv *env, jstring string, const char *utf)
{
	enter_vm_from_jni();

	free((char *)utf);
}
