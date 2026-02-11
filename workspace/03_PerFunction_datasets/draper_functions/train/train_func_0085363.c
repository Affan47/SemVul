Java_ncsa_hdf_hdflib_HDFLibrary_Vsetattr__ILjava_lang_String_2IILjava_lang_String_2
( JNIEnv *env,
jclass clss,
jint gr_id,
jstring attr_name,
jint data_type,
jint count,
jstring values)
{
    intn rval;
    char *str;
    char *val;

    str =(char *) ENVPTR->GetStringUTFChars(ENVPAR attr_name,0);
    val =(char *) ENVPTR->GetStringUTFChars(ENVPAR values,0);

    rval = Vsetattr((int32) gr_id, (char *)str, (int32) data_type,
        (int32) count, (VOIDP) val);

    ENVPTR->ReleaseStringUTFChars(ENVPAR attr_name,str);
    ENVPTR->ReleaseStringUTFChars(ENVPAR values,val);

    if (rval == FAIL) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}
