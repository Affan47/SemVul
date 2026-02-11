H5Z__check_unregister(hid_t ocpl_id, H5Z_filter_t filter_id)
{
    H5P_genplist_t  *plist;
    htri_t          ret_value = FALSE;

    FUNC_ENTER_STATIC


    if(NULL == (plist = H5P_object_verify(ocpl_id, H5P_OBJECT_CREATE)))
        HGOTO_ERROR(H5E_PLINE, H5E_BADATOM, FAIL, "can't find object for ID")


    if((ret_value = H5P_filter_in_pline(plist, filter_id)) < 0)
        HGOTO_ERROR(H5E_PLINE, H5E_CANTGET, FAIL, "can't check filter in pipeline")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
