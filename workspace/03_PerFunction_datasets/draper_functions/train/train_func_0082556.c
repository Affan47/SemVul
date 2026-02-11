Jam_GetStringUTFRegion(JNIEnv *env, jstring string_ref, jsize start,
                            jsize len, char *buf) {

    Object *string = REF_TO_OBJ(string_ref);

    if((start + len) > getStringLen(string))
        signalException(java_lang_StringIndexOutOfBoundsException, NULL);
    else
        StringRegion2Utf8(string, start, len, buf);
}
