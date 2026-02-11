Java_java_util_prefs_FileSystemPreferences_chmod(JNIEnv *env,
                       jclass thisclass, jstring java_fname, jint permission) {
    const char *fname = JNU_GetStringPlatformChars(env, java_fname, JNI_FALSE);
    int result;
    result =  chmod(fname, permission);
    if (result != 0)
       result = errno;
    JNU_ReleaseStringPlatformChars(env, java_fname, fname);
    return (jint) result;
}
