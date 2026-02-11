H5F_get_sohm_mesg_count_test(hid_t file_id, unsigned type_id,
    size_t *mesg_count)
{
    H5F_t	*file;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (file = (H5F_t *)H5I_object_verify(file_id, H5I_FILE)))
	HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not a file")


    if(H5SM_get_mesg_count_test(file, H5AC_ind_dxpl_id, type_id, mesg_count) < 0)
        HGOTO_ERROR(H5E_FILE, H5E_CANTGET, FAIL, "can't retrieve shared message count")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
