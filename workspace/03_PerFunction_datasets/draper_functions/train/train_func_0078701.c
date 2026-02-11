Java_ncsa_hdf_hdf5lib_H5_H5Sget_1select_1bounds(
            JNIEnv *env, jclass clss, jint spaceid, jlongArray start,
            jlongArray end) {
        herr_t status;
        jlong *startP, *endP;
        jboolean isCopy;
        hsize_t *strt;
        hsize_t *en;
        int rank;
        int i;

        if (start == NULL) {
            h5nullArgument(env, "H5Sget_select_bounds:  start is NULL");
            return -1;
        }

        if (end == NULL) {
            h5nullArgument(env, "H5Sget_select_bounds:  end is NULL");
            return -1;
        }

        startP = ENVPTR->GetLongArrayElements(ENVPAR start, &isCopy);
        if (startP == NULL) {
            h5JNIFatalError( env, "H5Sget_select_bounds:  start not pinned");
            return -1;
        }
        rank = (int)ENVPTR->GetArrayLength(ENVPAR start);
        strt = (hsize_t *)malloc( rank * sizeof(hsize_t));
        if (strt == NULL) {
            ENVPTR->ReleaseLongArrayElements(ENVPAR start,startP,JNI_ABORT);
            h5JNIFatalError(env,"H5Sget_select_bounds:  start not converted to hsize_t");
            return -1;
        }

        endP = ENVPTR->GetLongArrayElements(ENVPAR end,&isCopy);
        if (endP == NULL) {
            ENVPTR->ReleaseLongArrayElements(ENVPAR start,startP,JNI_ABORT);
            free(strt);
            h5JNIFatalError( env, "H5Sget_select_bounds:  end not pinned");
            return -1;
        }
        en = (hsize_t *)malloc( rank * sizeof(hsize_t));
        if (en == NULL)  {
            ENVPTR->ReleaseLongArrayElements(ENVPAR end,endP,JNI_ABORT);
            ENVPTR->ReleaseLongArrayElements(ENVPAR start,startP,JNI_ABORT);
            free(strt);
            h5JNIFatalError(env,  "H5Sget_simple_extent:  dims not converted to hsize_t");
            return -1;
        }

        status = H5Sget_select_bounds((hid_t) spaceid, (hsize_t *)strt, (hsize_t *)en);

        if (status < 0) {
            ENVPTR->ReleaseLongArrayElements(ENVPAR start,startP,JNI_ABORT);
            ENVPTR->ReleaseLongArrayElements(ENVPAR end,endP,JNI_ABORT);
            free(strt);
            free(en);
            h5libraryError(env);
            return -1;
        }

        for (i = 0; i < rank; i++) {
            startP[i] = strt[i];
            endP[i] = en[i];
        }
        ENVPTR->ReleaseLongArrayElements(ENVPAR start,startP,0);
        ENVPTR->ReleaseLongArrayElements(ENVPAR end,endP,0);
        free(strt);
        free(en);

        return (jint)status;
    }
