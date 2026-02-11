H5Fclear_elink_file_cache(hid_t file_id)
{
    H5F_t         *file;
    herr_t        ret_value = SUCCEED;

    FUNC_ENTER_API(H5Fclear_elink_file_cache, FAIL)
    H5TRACE1("e", "i", file_id);


    if(NULL == (file = (H5F_t *)H5I_object_verify(file_id, H5I_FILE)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "not a file ID")


    if(file->shared->efc)
        if(H5F_efc_release(file->shared->efc) < 0)
            HGOTO_ERROR(H5E_FILE, H5E_CANTRELEASE, FAIL, "can't release external file cache")

done:
    FUNC_LEAVE_API(ret_value)
}
