Java_ncsa_hdf_hdflib_HDFLibrary_GRreadimage
( JNIEnv *env,
jclass cls,
jint ri_id,
jintArray start,
jintArray stride,
jintArray edge,
jbyteArray data)
{
    intn rval;
    jbyte *arr;
    jint *strt;
    jint *strd;
    jint *edg;
    jboolean bb;

    arr = (jbyte *)ENVPTR->GetPrimitiveArrayCritical(ENVPAR data,&bb);

    strt = ENVPTR->GetIntArrayElements(ENVPAR start,&bb);
    if (stride == NULL) {
        strd = NULL;
    } else {
        strd = ENVPTR->GetIntArrayElements(ENVPAR stride,&bb);
    }
    edg = ENVPTR->GetIntArrayElements(ENVPAR edge,&bb);

    if (strd == NULL) {
        rval = GRreadimage((int32) ri_id, (int32 *)strt, (int32 *)NULL,
            (int32 *)edg, (VOIDP) arr);
    } else {
        rval = GRreadimage((int32) ri_id, (int32 *)strt, (int32 *)strd,
            (int32 *)edg, (VOIDP) arr);
    }

    ENVPTR->ReleaseIntArrayElements(ENVPAR start,strt,JNI_ABORT);
    if (stride != NULL) {
        ENVPTR->ReleaseIntArrayElements(ENVPAR stride,strd,JNI_ABORT);
    }
    ENVPTR->ReleaseIntArrayElements(ENVPAR edge,edg,JNI_ABORT);

    if (rval == FAIL) {
        ENVPTR->ReleasePrimitiveArrayCritical(ENVPAR data,arr,JNI_ABORT);
        return JNI_FALSE;
    } else {
        ENVPTR->ReleasePrimitiveArrayCritical(ENVPAR data,arr,0);
        return JNI_TRUE;
    }
}
