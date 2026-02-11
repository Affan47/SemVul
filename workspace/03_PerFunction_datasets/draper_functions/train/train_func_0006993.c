H5G__compact_remove_by_idx(const H5O_loc_t *oloc, hid_t dxpl_id,
    const H5O_linfo_t *linfo, H5RS_str_t *grp_full_path_r, H5_index_t idx_type,
    H5_iter_order_t order, hsize_t n)
{
    H5G_link_table_t ltable = {0, NULL};
    H5G_iter_rm_t udata;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_PACKAGE

    HDassert(oloc && oloc->file);
    HDassert(linfo);


    if(H5G_compact_build_table(oloc, dxpl_id, linfo, idx_type, order, &ltable) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "can't create link message table")


    if(n >= ltable.nlinks)
	HGOTO_ERROR(H5E_ARGS, H5E_BADRANGE, FAIL, "index out of bound")


    udata.file = oloc->file;
    udata.dxpl_id = dxpl_id;
    udata.grp_full_path_r = grp_full_path_r;
    udata.name = ltable.lnks[n].name;


    if(H5O_msg_remove_op(oloc, H5O_LINK_ID, H5O_FIRST, H5G_compact_remove_common_cb, &udata, TRUE, dxpl_id) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_CANTDELETE, FAIL, "unable to delete link message")

done:

    if(ltable.lnks && H5G__link_release_table(&ltable) < 0)
        HDONE_ERROR(H5E_SYM, H5E_CANTFREE, FAIL, "unable to release link table")

    FUNC_LEAVE_NOAPI(ret_value)
}
