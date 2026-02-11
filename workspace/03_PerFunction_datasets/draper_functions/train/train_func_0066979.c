H5P__ocrt_close(hid_t dcpl_id, void UNUSED *close_data)
{
    H5O_pline_t     pline;
    H5P_genplist_t *plist;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_STATIC


    if(NULL == (plist = (H5P_genplist_t *)H5I_object(dcpl_id)))
        HGOTO_ERROR(H5E_ARGS, H5E_BADTYPE, FAIL, "not an object creation property list")


    if(H5P_get(plist, H5O_CRT_PIPELINE_NAME, &pline) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTGET, FAIL, "can't get pipeline")


    if(H5O_msg_reset(H5O_PLINE_ID, &pline) < 0)
        HGOTO_ERROR(H5E_PLIST, H5E_CANTFREE, FAIL, "can't release pipeline info")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
