Java_ncsa_hdf_hdf5lib_H5_H5Dread_1int
  (JNIEnv *env, jclass clss, jint dataset_id, jint mem_type_id, jint mem_space_id,
  jint file_space_id, jint xfer_plist_id, jintArray buf, jboolean isCriticalPinning)
{
    herr_t   status;
    jint    *buffP;
    jboolean isCopy;
    htri_t data_class;


    data_class = H5Tdetect_class(mem_type_id, H5T_VLEN);
    if((data_class == 1) || (data_class < 0)) {
        h5badArgument( env, "H5Dread:  buf does not support variable length type");
        return -1;
    }

    data_class = H5Tdetect_variable_str(mem_type_id);
    if((data_class == 1) || (data_class < 0)) {
        h5badArgument( env, "H5Dread:  buf does not support variable length string type");
        return -1;
    }

    if (buf == NULL) {
        h5nullArgument(env, "H5Dread:  buf is NULL");
        return -1;
    }

    PIN_INT_ARRAY();
    if (buffP == NULL) {
        h5JNIFatalError(env, "H5Dread:  buf not pinned");
        return -1;
    }

    status = H5Dread((hid_t)dataset_id, (hid_t)mem_type_id, (hid_t)mem_space_id,
                     (hid_t)file_space_id, (hid_t)xfer_plist_id, buffP);

    if (status < 0) {
        UNPIN_INT_ARRAY(JNI_ABORT);
        h5libraryError(env);
        return -1;
    }

    UNPIN_INT_ARRAY(0);

    return (jint)status;
}
