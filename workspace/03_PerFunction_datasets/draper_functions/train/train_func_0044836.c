Java_ncsa_hdf_hdflib_HDFLibrary_VSisattr
( JNIEnv *env,
jclass clss,
jint id)
{
    intn rval;

    rval = VSisattr((int32) id);
    if (rval == 0) {
        return JNI_FALSE;
    } else {
        return JNI_TRUE;
    }
}
