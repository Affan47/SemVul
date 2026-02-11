Java_ncsa_hdf_hdflib_HDFLibrary_ANannlist
( JNIEnv *env,
jclass clss,
jint an_id,
jint anntype,
jshort tag,
jshort ref,
jintArray annlist
)
{
    intn retVal;
    jint *iarr;
    jboolean bb;

    iarr = ENVPTR->GetIntArrayElements(ENVPAR annlist,&bb);

    retVal = ANannlist((int32)an_id, (ann_type)anntype,
        (uint16)tag,(uint16)ref,(int32 *)iarr);

    if (retVal == FAIL) {
        ENVPTR->ReleaseIntArrayElements(ENVPAR annlist,iarr,JNI_ABORT);
    } else {
        ENVPTR->ReleaseIntArrayElements(ENVPAR annlist,iarr,0);
    }
    return (jint)retVal;
}
