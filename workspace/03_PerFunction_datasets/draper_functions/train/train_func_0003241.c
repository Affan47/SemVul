Java_ncsa_hdf_hdflib_HDFDeprecated_DFSDgetNT
( JNIEnv *env,
jclass clss,
jintArray data_type)
{
    intn rval;
    jint *dt;
    jboolean bb;

    dt = ENVPTR->GetIntArrayElements(ENVPAR data_type,&bb);
    if (dt == NULL) {

        return(JNI_FALSE);
    }

    rval = DFSDgetNT((int32 *)&(dt[0]));

    if (rval == FAIL) {
        ENVPTR->ReleaseIntArrayElements(ENVPAR data_type,dt,JNI_ABORT);
        return JNI_FALSE;
    } else {
        ENVPTR->ReleaseIntArrayElements(ENVPAR data_type,dt,0);
        return JNI_TRUE;
    }
}
