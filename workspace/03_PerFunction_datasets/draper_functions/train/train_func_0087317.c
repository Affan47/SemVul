Java_ncsa_hdf_hdflib_HDFLibrary_SDwritechunk
( JNIEnv *env,
jclass clss,
jint sdid,
jintArray index,
jbyteArray dat)
{
int32 retVal;
jbyte * s;
jint * arr;
    jboolean bb;

    s = ENVPTR->GetByteArrayElements(ENVPAR dat,&bb);
    arr = ENVPTR->GetIntArrayElements(ENVPAR index,&bb);

    retVal = SDwritechunk((int32)sdid,(int32 *)arr,(char *)s);

    ENVPTR->ReleaseByteArrayElements(ENVPAR dat,s,JNI_ABORT);
    ENVPTR->ReleaseIntArrayElements(ENVPAR index,arr,JNI_ABORT);

    if (retVal == FAIL) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}
