Java_ncsa_hdf_hdf5lib_H5_H5Pset_1alignment
  (JNIEnv *env, jclass clss, jint plist, jlong threshold, jlong alignment)
{
    long   thr;
    long   align;
    herr_t retVal = -1;

    thr = (long)threshold;
    align = (long)alignment;

    retVal = H5Pset_alignment((hid_t)plist, (hsize_t)thr, (hsize_t)align);
    if (retVal < 0) {
        h5libraryError(env);
    }

    return (jint)retVal;
}
