H5O_get_nlinks(const H5O_loc_t *loc, hid_t dxpl_id, hsize_t *nlinks)
{
    H5O_t *oh = NULL;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5O_get_nlinks, FAIL)


    HDassert(loc);
    HDassert(nlinks);


    if(NULL == (oh = H5O_protect(loc, dxpl_id, H5AC_READ)))
	HGOTO_ERROR(H5E_OHDR, H5E_CANTPROTECT, FAIL, "unable to load object header")


    *nlinks = oh->link_msgs_seen;

done:
    if(oh && H5O_unprotect(loc, dxpl_id, oh, H5AC__NO_FLAGS_SET) < 0)
	HDONE_ERROR(H5E_OHDR, H5E_CANTUNPROTECT, FAIL, "unable to release object header")

    FUNC_LEAVE_NOAPI(ret_value)
}
