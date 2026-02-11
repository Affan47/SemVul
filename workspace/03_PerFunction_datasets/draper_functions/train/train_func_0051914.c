Java_ncsa_hdf_hdf5lib_H5_H5Literate
      (JNIEnv *env, jclass clss, jint grp_id, jint idx_type, jint order,
              jlong idx, jobject callback_op, jobject op_data)
    {
        hsize_t       start_idx = (hsize_t)idx;
        herr_t        status = -1;

        ENVPTR->GetJavaVM(ENVPAR &jvm);
        visit_callback = callback_op;

        if (op_data == NULL) {
            h5nullArgument(env,  "H5Literate:  op_data is NULL");
            return -1;
        }
        if (callback_op == NULL) {
            h5nullArgument(env,  "H5Literate:  callback_op is NULL");
            return -1;
        }

        status = H5Literate((hid_t)grp_id, (H5_index_t)idx_type, (H5_iter_order_t)order, (hsize_t*)&start_idx, (H5L_iterate_t)H5L_iterate_cb, (void*)op_data);

        if (status < 0) {
           h5libraryError(env);
           return status;
        }

        return status;
    }
