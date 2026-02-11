getFrameTypeID(JNIEnv *env, jobject jFtype) {
    cpl_frame_type id = CPL_FRAME_TYPE_NONE;
    jstring jIdname = (jstring)0;
    const char *idname = (char *)0;
    int done = 0;
    int ok = 1;

    ok = ok &&
            jFtype &&
            (!(*env)->ExceptionCheck(env)) &&
            (jIdname = (*env)->GetObjectField(env, jFtype, FrameTypeIDNameField)) &&
            (idname = (*env)->GetStringUTFChars(env, jIdname, NULL));
    if (ok) {
        TEST_ID_NAME(CPL_FRAME_TYPE_NONE)
                else TEST_ID_NAME(CPL_FRAME_TYPE_IMAGE)
                else TEST_ID_NAME(CPL_FRAME_TYPE_MATRIX)
                else TEST_ID_NAME(CPL_FRAME_TYPE_TABLE)
    }
    if (!done && (*env)->ExceptionCheck(env)) {
        (*env)->ThrowNew(env, RuntimeExceptionClass, "Unknown frame type ID");
    }
    return id;
}
