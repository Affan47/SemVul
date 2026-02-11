Java_ncsa_hdf_hdflib_HDFDeprecated_DFSDgetrange
( JNIEnv *env,
jclass clss,
jbyteArray max,
jbyteArray min)
{
        int32 retVal;
        jbyte *minp, *maxp;
        jboolean bb;

        maxp = ENVPTR->GetByteArrayElements(ENVPAR max,&bb);
        minp = ENVPTR->GetByteArrayElements(ENVPAR min,&bb);

        retVal = DFSDgetrange(maxp, minp);

        if (retVal==FAIL) {
                ENVPTR->ReleaseByteArrayElements(ENVPAR max,maxp,JNI_ABORT);
                ENVPTR->ReleaseByteArrayElements(ENVPAR min,minp,JNI_ABORT);
                return JNI_FALSE;
        }
        else {
                ENVPTR->ReleaseByteArrayElements(ENVPAR max,maxp,0);
                ENVPTR->ReleaseByteArrayElements(ENVPAR min,minp,0);
                return JNI_TRUE;
        }
}
