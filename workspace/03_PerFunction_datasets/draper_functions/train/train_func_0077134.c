Java_ncsa_hdf_hdf5lib_H5_H5Freset_1mdc_1hit_1rate_1stats
  (JNIEnv *env, jclass cls, jint file_id)
{
    herr_t ret_val = -1;

    ret_val = H5Freset_mdc_hit_rate_stats((hid_t)file_id);

    if (ret_val < 0) {
        h5libraryError(env);
    }
}
