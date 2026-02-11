Java_ncsa_hdf_hdf5lib_H5_H5Pset_1meta_1block_1size
  (JNIEnv *env, jclass clss, jint plist, jlong size)
{
    long   sz;
    herr_t status = -1;

    sz = (long)size;

    status = H5Pset_meta_block_size((hid_t)plist, (hsize_t)sz);
    if (status < 0) {
        h5libraryError(env);
    }
}
