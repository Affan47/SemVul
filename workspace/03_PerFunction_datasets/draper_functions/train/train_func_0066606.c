Java_ncsa_hdf_hdf5lib_H5__1H5Dget_1space_1status
  (JNIEnv *env, jclass clss, jint dset_id, jintArray status)
{
    jint    *theArray;
    jboolean isCopy;
    H5D_space_status_t space_status;
    herr_t   retVal = -1;

    if (status == NULL) {

        h5nullArgument(env, "H5Dget_space_status:  status is NULL");
        return -1;
    }
    theArray = (jint*)ENVPTR->GetIntArrayElements(ENVPAR status, &isCopy);
    if (theArray == NULL) {
        h5JNIFatalError(env, "H5Dget_space_status:  status not pinned");
        return -1;
    }

    retVal = H5Dget_space_status((hid_t)dset_id, (H5D_space_status_t*)&space_status );

    if (retVal < 0) {
        ENVPTR->ReleaseIntArrayElements(ENVPAR status, theArray, JNI_ABORT);
        h5libraryError(env);
        return -1;
    }

    theArray[0] = space_status;
    ENVPTR->ReleaseIntArrayElements(ENVPAR status, theArray, 0);

    return (jint)retVal;
}
