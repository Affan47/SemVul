Java_ncsa_hdf_hdflib_HDFLibrary_SDcheckempty
( JNIEnv *env,
jclass clss,
jint sdsid,
jintArray emptySDS)
{
    int32 retVal;
    jboolean bb;


    intn *isempty;

    isempty = (intn *)ENVPTR->GetIntArrayElements(ENVPAR emptySDS,&bb);

    retVal = SDcheckempty((int32)sdsid, (intn *)isempty );

    ENVPTR->ReleaseIntArrayElements(ENVPAR emptySDS,(jint *)isempty,0);
    if (retVal == FAIL) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}
