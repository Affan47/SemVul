H5G__compact_get_name_by_idx(const H5O_loc_t *oloc, hid_t dxpl_id,
    const H5O_linfo_t *linfo, H5_index_t idx_type, H5_iter_order_t order,
    hsize_t idx, char* name, size_t size)
{
    H5G_link_table_t    ltable = {0, NULL};
    ssize_t		ret_value;

    FUNC_ENTER_PACKAGE


    HDassert(oloc);


    if(H5G_compact_build_table(oloc, dxpl_id, linfo, idx_type, order, &ltable) < 0)
        HGOTO_ERROR(H5E_SYM, H5E_CANTINIT, FAIL, "can't create link message table")


    if(idx >= ltable.nlinks)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "index out of bound")


    ret_value = (ssize_t)HDstrlen(ltable.lnks[idx].name);


    if(name) {
        HDstrncpy(name, ltable.lnks[idx].name, MIN((size_t)(ret_value + 1), size));
        if((size_t)ret_value >= size)
            name[size - 1]='\0';
    }

done:

    if(ltable.lnks && H5G__link_release_table(&ltable) < 0)
        HDONE_ERROR(H5E_SYM, H5E_CANTFREE, FAIL, "unable to release link table")

    FUNC_LEAVE_NOAPI(ret_value)
}
