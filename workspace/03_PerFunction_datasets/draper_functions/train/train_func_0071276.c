H5O_msg_count(const H5O_loc_t *loc, unsigned type_id, hid_t dxpl_id)
{
    H5O_t *oh = NULL;
    const H5O_msg_class_t *type;
    int	ret_value;

    FUNC_ENTER_NOAPI(H5O_msg_count, FAIL)


    HDassert(loc);
    HDassert(loc->file);
    HDassert(H5F_addr_defined(loc->addr));
    HDassert(type_id < NELMTS(H5O_msg_class_g));
    type = H5O_msg_class_g[type_id];
    HDassert(type);


    if(NULL == (oh = H5O_protect(loc, dxpl_id, H5AC_READ)))
	HGOTO_ERROR(H5E_OHDR, H5E_CANTPROTECT, FAIL, "unable to protect object header")


    ret_value = H5O_msg_count_real(oh, type);

done:
    if(oh && H5O_unprotect(loc, dxpl_id, oh, H5AC__NO_FLAGS_SET) < 0)
	HDONE_ERROR(H5E_OHDR, H5E_CANTUNPROTECT, FAIL, "unable to release object header")

    FUNC_LEAVE_NOAPI(ret_value)
}
