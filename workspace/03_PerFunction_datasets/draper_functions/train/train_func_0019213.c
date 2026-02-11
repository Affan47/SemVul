H5A_get_shared_rc_test(hid_t attr_id, hsize_t *ref_count)
{
    H5A_t	*attr;
    herr_t	ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (attr = (H5A_t *)H5I_object_verify(attr_id, H5I_ATTR)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not an attribute")


    HDassert(H5O_msg_is_shared(H5O_ATTR_ID, attr));


    if(H5SM_get_refcount(attr->oloc.file, H5AC_ind_dxpl_id, H5O_ATTR_ID,
            &attr->sh_loc, ref_count) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_CANTGET, FAIL, "can't retrieve shared message ref count")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
