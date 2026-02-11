Jam_GetStringRegion(JNIEnv *env, jstring string_ref, jsize start,
                         jsize len, jchar *buf) {

    Object *string = REF_TO_OBJ(string_ref);

    if((start + len) > getStringLen(string))
        signalException(java_lang_StringIndexOutOfBoundsException, NULL);
    else
        memcpy(buf, getStringChars(string) + start, len * sizeof(short));
}
