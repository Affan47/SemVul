Java_ncsa_hdf_hdflib_HDFDeprecated_DFSDgetdims
( JNIEnv *env,
jclass clss,
jstring filename,
jintArray rank,
jintArray dimsizes,
jint maxrank)
{
    intn rval;
    jchar * name;
    jint * dims;
    jint * rnk;
    jboolean bb;

    name =(jchar *) ENVPTR->GetStringUTFChars(ENVPAR filename,0);
    dims = (jint *)ENVPTR->GetIntArrayElements(ENVPAR dimsizes,&bb);
    rnk = (jint *)ENVPTR->GetIntArrayElements(ENVPAR rank,&bb);


    rval = DFSDgetdims((char *)name, (intn *)&(rnk[0]), (int32 *)dims, (intn) maxrank);

    ENVPTR->ReleaseStringUTFChars(ENVPAR filename,(char *)name);
    if (rval==FAIL) {
        ENVPTR->ReleaseIntArrayElements(ENVPAR dimsizes,dims,JNI_ABORT);
        ENVPTR->ReleaseIntArrayElements(ENVPAR rank,rnk,JNI_ABORT);
        return JNI_FALSE;
    } else {
        ENVPTR->ReleaseIntArrayElements(ENVPAR dimsizes,dims,0);
        ENVPTR->ReleaseIntArrayElements(ENVPAR rank,rnk,0);
        return JNI_TRUE;
    }
}
