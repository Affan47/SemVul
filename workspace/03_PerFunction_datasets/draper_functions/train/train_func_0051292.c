H5G_traverse_special(const H5G_loc_t *grp_loc, const H5O_link_t *lnk,
    unsigned target, size_t *nlinks, hbool_t last_comp,
    H5G_loc_t *obj_loc, hbool_t *obj_exists, hid_t lapl_id, hid_t dxpl_id)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5G_traverse_special, FAIL)


    HDassert(grp_loc);
    HDassert(lnk);
    HDassert(obj_loc);
    HDassert(nlinks);


    if(H5L_TYPE_SOFT == lnk->type &&
            (0 == (target & H5G_TARGET_SLINK) || !last_comp)) {
        if((*nlinks)-- <= 0)
            HGOTO_ERROR(H5E_LINK, H5E_NLINKS, FAIL, "too many links")
        if(H5G_traverse_slink(grp_loc, lnk, obj_loc, (target & H5G_TARGET_EXISTS), nlinks, obj_exists, lapl_id, dxpl_id) < 0)
            HGOTO_ERROR(H5E_LINK, H5E_TRAVERSE, FAIL, "symbolic link traversal failed")
    }


    if(lnk->type >= H5L_TYPE_UD_MIN &&
            (0 == (target & H5G_TARGET_UDLINK) || !last_comp) ) {
        if((*nlinks)-- <= 0)
            HGOTO_ERROR(H5E_LINK, H5E_NLINKS, FAIL, "too many links")
        if(H5G_traverse_ud(grp_loc, lnk, obj_loc, (target & H5G_TARGET_EXISTS), nlinks, obj_exists, lapl_id, dxpl_id) < 0)
            HGOTO_ERROR(H5E_LINK, H5E_TRAVERSE, FAIL, "user-defined link traversal failed")
    }


    if(H5F_addr_defined(obj_loc->oloc->addr) &&
            (0 == (target & H5G_TARGET_MOUNT) || !last_comp)) {
        if(H5G_traverse_mount(obj_loc) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_NOTFOUND, FAIL, "mount point traversal failed")
    }


    if(grp_loc->oloc->holding_file && grp_loc->oloc->file == obj_loc->oloc->file)
        if(H5O_loc_hold_file(obj_loc->oloc) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTOPENOBJ, FAIL, "unable to hold file open")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
