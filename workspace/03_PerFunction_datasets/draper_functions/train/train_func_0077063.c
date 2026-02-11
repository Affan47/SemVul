Java_ncsa_hdf_hdflib_HDFDeprecated_DFSDreadref
( JNIEnv *env,
jclass clss,
jstring filename,
jshort ref)
{
    intn rval;
    jchar * name;

    name =(jchar *) ENVPTR->GetStringUTFChars(ENVPAR filename,0);

    rval = DFSDreadref((char *)name, (uint16) ref);
    ENVPTR->ReleaseStringUTFChars(ENVPAR filename,(char *)name);
    if (rval==FAIL) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }

}
