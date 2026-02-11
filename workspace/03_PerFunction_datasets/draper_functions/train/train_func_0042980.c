newString646_US(JNIEnv *env, const char *str)
{
    int len = strlen(str);
    jchar buf[512];
    jchar *str1;
    jstring result;
    int i;

    if (len > 512) {
        str1 = (jchar *)malloc(len * sizeof(jchar));
        if (str1 == 0) {
            JNU_ThrowOutOfMemoryError(env, 0);
            return 0;
        }
    } else
        str1 = buf;

    for (i=0; i<len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (c <= 0x7f)
            str1[i] = c;
        else
            str1[i] = '?';
    }

    result = (*env)->NewString(env, str1, len);
    if (str1 != buf)
        free(str1);
    return result;
}
