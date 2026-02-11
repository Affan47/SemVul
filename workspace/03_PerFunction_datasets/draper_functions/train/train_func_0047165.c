Java_ncsa_hdf_hdf5lib_H5_H5Pget_1gcreferences
  (JNIEnv *env, jclass clss, jint fapl_id)
{
    herr_t    status;
    unsigned  gc_ref_val = 0;

    status = H5Pget_gc_references((hid_t)fapl_id, (unsigned *)&gc_ref_val);
    if (status < 0) {
        h5libraryError(env);
        return JNI_FALSE;
    }

    if (gc_ref_val == 1) {
        return JNI_TRUE;
    }
    return JNI_FALSE;
}
