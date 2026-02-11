getUTF(JNIEnv *env, jstring str, char* localBuf, int bufSize)
{
    char* utfStr = NULL;

    int len = (*env)->GetStringUTFLength(env, str);
    int unicode_len = (*env)->GetStringLength(env, str);
    if (len >= bufSize) {
        utfStr = malloc(len + 1);
        if (utfStr == NULL) {
            JNU_ThrowOutOfMemoryError(env, NULL);
            return NULL;
        }
    } else {
        utfStr = localBuf;
    }
    (*env)->GetStringUTFRegion(env, str, 0, unicode_len, utfStr);

    return utfStr;
}
