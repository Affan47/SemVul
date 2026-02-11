Java_ncsa_hdf_hdf5lib_H5_H5Eget_1current_1stack
      (JNIEnv *env, jclass cls)
    {
        hid_t ret_val = H5Eget_current_stack();
        if (ret_val < 0) {
            h5libraryError(env);
            return -1;
        }
        return ret_val;
    }
