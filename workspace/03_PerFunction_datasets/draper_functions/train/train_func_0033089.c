H5G_get_objinfo(const H5G_loc_t *loc, const char *name, hbool_t follow_link,
    H5G_stat_t *statbuf, hid_t dxpl_id)
{
    H5G_trav_goi_t udata;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5G_get_objinfo)

    HDassert(loc);
    HDassert(name && *name);


    if(statbuf)
        HDmemset(statbuf, 0, sizeof(H5G_stat_t));


    udata.statbuf = statbuf;
    udata.follow_link = follow_link;
    udata.loc_file = loc->oloc->file;
    udata.dxpl_id = dxpl_id;


    if(H5G_traverse(loc, name, (unsigned)(follow_link ? H5G_TARGET_NORMAL : H5G_TARGET_SLINK|H5G_TARGET_UDLINK),
            H5G_get_objinfo_cb, &udata, H5P_DEFAULT, dxpl_id) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_EXISTS, FAIL, "name doesn't exist")


    if(statbuf && follow_link == 0) {
        H5L_info_t linfo;
        herr_t ret;


        H5E_BEGIN_TRY {
            ret = H5L_get_info(loc, name, &linfo, H5P_DEFAULT, dxpl_id);
        } H5E_END_TRY

        if(ret >= 0 && linfo.type != H5L_TYPE_HARD) {
            statbuf->linklen = linfo.u.val_size;
            if(linfo.type == H5L_TYPE_SOFT)
                statbuf->type = H5G_LINK;
            else {
                HDassert(linfo.type >= H5L_TYPE_UD_MIN && linfo.type <= H5L_TYPE_MAX);
                statbuf->type = H5G_UDLINK;
            }
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
