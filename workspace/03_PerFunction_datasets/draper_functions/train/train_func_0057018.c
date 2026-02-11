Java_ncsa_hdf_hdflib_HDFLibrary_SDgetchunkinfo
( JNIEnv *env,
jclass clss,
jint sdsid,
jobject chunk_def,
jintArray cflags)
{
int32 rval;
HDF_CHUNK_DEF cdef;
jboolean stat;
jint *flgs;
jboolean bb;


    flgs = ENVPTR->GetIntArrayElements(ENVPAR cflags,&bb);
    rval = SDgetchunkinfo( (int32)sdsid, &cdef, (int32 *)&(flgs[0]));


    if (rval == FAIL) {
        ENVPTR->ReleaseIntArrayElements(ENVPAR cflags,(jint *)flgs,JNI_ABORT);
        return JNI_FALSE;
    } else {
        stat = makeChunkInfo( env, chunk_def, (int32)*flgs, &cdef);
        ENVPTR->ReleaseIntArrayElements(ENVPAR cflags,(jint *)flgs,0);

        return stat;
    }

}
