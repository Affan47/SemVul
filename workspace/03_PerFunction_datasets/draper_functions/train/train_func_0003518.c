Java_ncsa_hdf_hdf5lib_H5__1H5Pclose
  (JNIEnv *env, jclass clss, jint plist)
{
    herr_t retVal = 0;

    if (plist > 0)
        retVal = H5Pclose((hid_t)plist);

    if (retVal < 0) {
        h5libraryError(env);
    }

    return (jint)retVal;
}
