Java_ncsa_hdf_hdf5lib_H5_H5Pset_1fapl_1windows
  (JNIEnv *env, jclass clss, jint fapl_id)
{
    herr_t retVal = -1;

#ifdef H5_HAVE_WINDOWS
    retVal = H5Pset_fapl_windows((hid_t) fapl_id);
#endif
    if (retVal < 0) {
        h5libraryError(env);
    }

    return (jint)retVal;
}
