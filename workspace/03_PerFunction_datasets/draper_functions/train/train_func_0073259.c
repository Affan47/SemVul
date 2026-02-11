Java_ncsa_hdf_hdf5lib_H5_H5Gget_1info_1by_1name
  (JNIEnv *env, jclass cls, jint loc_id, jstring name, jint lapl_id)
{
    H5G_info_t group_info;
    herr_t ret_val = -1;
    char* gName;
    jboolean isCopy;

    if (name == NULL) {
        h5nullArgument( env, "H5Gget_info_by_name:  name is NULL");
        return NULL;
    }

    gName = (char *)ENVPTR->GetStringUTFChars(ENVPAR name,&isCopy);

    if (gName == NULL) {
        h5JNIFatalError( env, "H5Gget_info_by_name:  file name not pinned");
        return NULL;
    }

    ret_val = H5Gget_info_by_name((hid_t)loc_id, gName, &group_info, (hid_t)lapl_id);

    ENVPTR->ReleaseStringUTFChars(ENVPAR name,gName);

    if (ret_val < 0) {
        h5libraryError(env);
        return NULL;
    }

    return create_H5G_info_t(env, group_info);
}
