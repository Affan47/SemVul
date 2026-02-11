H5L_get_info(const H5G_loc_t *loc, const char *name,
    H5L_info_t *linfo, hid_t lapl_id, hid_t dxpl_id)
{
    H5L_trav_gi_t udata;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(FAIL)

    udata.linfo = linfo;
    udata.dxpl_id = dxpl_id;


    if(H5G_traverse(loc, name, H5G_TARGET_SLINK|H5G_TARGET_UDLINK, H5L_get_info_cb, &udata, lapl_id, dxpl_id) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_EXISTS, FAIL, "name doesn't exist")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
