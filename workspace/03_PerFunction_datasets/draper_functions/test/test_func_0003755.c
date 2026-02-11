Java_ncsa_hdf_hdf5lib_H5_H5Pget_1chunk
  (JNIEnv *env, jclass clss, jint plist, jint max_ndims, jlongArray dims)
{
    herr_t   status;
    jlong   *theArray;
    jboolean isCopy;
    hsize_t *da;
    int      i;

    if (dims == NULL) {
        h5nullArgument(env, "H5Pget_chunk:  dims is NULL");
        return -1;
    }
    if (ENVPTR->GetArrayLength(ENVPAR dims) < max_ndims) {
        h5badArgument(env, "H5Pget_chunk:  dims array < max_ndims");
        return -1;
    }
    theArray = (jlong *)ENVPTR->GetLongArrayElements(ENVPAR dims, &isCopy);
    if (theArray == NULL) {
        h5JNIFatalError(env, "H5Pget_chunk:  input dims not pinned");
        return -1;
    }
    da = (hsize_t *)malloc(max_ndims * sizeof(hsize_t));
    if (da == NULL) {
        ENVPTR->ReleaseLongArrayElements(ENVPAR dims, theArray, JNI_ABORT);
        h5JNIFatalError(env, "H5Pget_chunk:  dims not converted to hsize_t");
        return -1;
    }

    status = H5Pget_chunk((hid_t)plist, (int)max_ndims, da);

    if (status < 0)  {
        ENVPTR->ReleaseLongArrayElements(ENVPAR dims, theArray, JNI_ABORT);
        free (da);
        h5libraryError(env);
        return -1;
    }
    for (i = 0; i < max_ndims; i++) {
        theArray[i] = da[i];
    }
    free (da);
    ENVPTR->ReleaseLongArrayElements(ENVPAR dims, theArray, 0);

    return (jint)status;
}
