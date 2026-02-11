Java_ncsa_hdf_hdf5lib_H5_H5Pget_1fill_1value
  (JNIEnv *env, jclass clss, jint plist_id, jint type_id, jbyteArray value)
{
    jint     status;
    jbyte   *byteP;
    jboolean isCopy;

    if (value == NULL) {
        h5badArgument(env, "H5Pget_fill_value:  value is NULL");
        return -1;
    }
    byteP = ENVPTR->GetByteArrayElements(ENVPAR value, &isCopy);
    if (byteP == NULL) {
        h5JNIFatalError(env, "H5Pget_fill_value:  value array not pinned");
        return -1;
    }

    status = H5Pget_fill_value((hid_t)plist_id, (hid_t)type_id, byteP);
    if (status < 0) {
        ENVPTR->ReleaseByteArrayElements(ENVPAR value, byteP, JNI_ABORT);
        h5libraryError(env);
        return -1;
    }
    ENVPTR->ReleaseByteArrayElements(ENVPAR value, byteP, 0);

    return status;
}
