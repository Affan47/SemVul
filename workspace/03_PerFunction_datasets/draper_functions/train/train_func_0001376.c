Java_ncsa_hdf_hdf5lib_H5_H5Pget_1btree_1ratios
  (JNIEnv *env, jclass clss, jint plist_id, jdoubleArray left, jdoubleArray middle, jdoubleArray right)
{
    herr_t   status;
    jdouble *leftP;
    jdouble *middleP;
    jdouble *rightP;
    jboolean isCopy;

    if (left == NULL) {
        h5nullArgument(env, "H5Pget_btree_ratios:  left input array is NULL");
        return -1;
    }
    if (middle == NULL) {
        h5nullArgument(env, "H5Pget_btree_ratios:  middle input array is NULL");
        return -1;
    }
    if (right == NULL) {
        h5nullArgument(env, "H5Pget_btree_ratios:  right input array is NULL");
        return -1;
    }

    leftP = (jdouble *)ENVPTR->GetDoubleArrayElements(ENVPAR left, &isCopy);
    if (leftP == NULL) {
        h5JNIFatalError(env, "H5Pget_btree_ratios:  left not pinned");
        return -1;
    }
    middleP = (jdouble *)ENVPTR->GetDoubleArrayElements(ENVPAR middle, &isCopy);
    if (middleP == NULL) {
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR left, leftP, JNI_ABORT);
        h5JNIFatalError(env, "H5Pget_btree_ratios:  middle not pinned");
        return -1;
    }
    rightP = (jdouble *)ENVPTR->GetDoubleArrayElements(ENVPAR right, &isCopy);
    if (rightP == NULL) {
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR left, leftP, JNI_ABORT);
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR middle, middleP, JNI_ABORT);
        h5JNIFatalError(env, "H5Pget_btree_ratios:  middle not pinned");
        return -1;
    }

    status = H5Pget_btree_ratios((hid_t)plist_id, (double *)leftP,
             (double *)middleP, (double *)rightP);
    if (status < 0) {
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR left, leftP, JNI_ABORT);
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR middle, middleP, JNI_ABORT);
        ENVPTR->ReleaseDoubleArrayElements(ENVPAR right, rightP, JNI_ABORT);
        h5libraryError(env);
        return -1;
    }
    ENVPTR->ReleaseDoubleArrayElements(ENVPAR left, leftP, 0);
    ENVPTR->ReleaseDoubleArrayElements(ENVPAR middle, middleP, 0);
    ENVPTR->ReleaseDoubleArrayElements(ENVPAR right, rightP, 0);

    return (jint)status;
}
