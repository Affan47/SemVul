H5G__node_by_idx(H5F_t *f, hid_t dxpl_id, const void UNUSED *_lt_key, haddr_t addr,
		  const void UNUSED *_rt_key, void *_udata)
{
    H5G_bt_it_idx_common_t	*udata = (H5G_bt_it_idx_common_t *)_udata;
    H5G_node_t		*sn = NULL;
    int                 ret_value = H5_ITER_CONT;

    FUNC_ENTER_PACKAGE


    HDassert(f);
    HDassert(H5F_addr_defined(addr));
    HDassert(udata);


    if(NULL == (sn = (H5G_node_t *)H5AC_protect(f, dxpl_id, H5AC_SNODE, addr, f, H5AC_READ)))
	HGOTO_ERROR(H5E_SYM, H5E_CANTLOAD, H5_ITER_ERROR, "unable to load symbol table node");


    if(udata->idx >= udata->num_objs && udata->idx < (udata->num_objs + sn->nsyms)) {
        hsize_t ent_idx;


        ent_idx = udata->idx - udata->num_objs;


        HDassert(udata->op);
        if((udata->op)(&sn->entry[ent_idx], udata) < 0)
            HGOTO_ERROR(H5E_SYM, H5E_CANTGET, H5B_INS_ERROR, "'by index' callback failed")


        ret_value = H5_ITER_STOP;
    }
    else
        udata->num_objs += sn->nsyms;

done:
    if(sn && H5AC_unprotect(f, dxpl_id, H5AC_SNODE, addr, sn, H5AC__NO_FLAGS_SET) < 0)
        HDONE_ERROR(H5E_SYM, H5E_PROTECT, H5_ITER_ERROR, "unable to release object header")

    FUNC_LEAVE_NOAPI(ret_value)
}
