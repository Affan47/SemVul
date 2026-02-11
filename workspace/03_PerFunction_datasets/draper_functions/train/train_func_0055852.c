H5B_get_info_helper(H5F_t *f, hid_t dxpl_id, const H5B_class_t *type, haddr_t addr,
    const H5B_info_ud_t *info_udata)
{
    H5B_t *bt = NULL;
    H5RC_t *rc_shared;
    H5B_shared_t *shared;
    H5B_cache_ud_t cache_udata;
    unsigned level;
    size_t sizeof_rnode;
    haddr_t next_addr;
    haddr_t left_child;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(type);
    HDassert(H5F_addr_defined(addr));
    HDassert(info_udata);
    HDassert(info_udata->bt_info);
    HDassert(info_udata->udata);


    if(NULL == (rc_shared = (type->get_shared)(f, info_udata->udata)))
	HGOTO_ERROR(H5E_BTREE, H5E_CANTGET, FAIL, "can't retrieve B-tree's shared ref. count object")
    shared = (H5B_shared_t *)H5RC_GET_OBJ(rc_shared);
    HDassert(shared);


    sizeof_rnode = shared->sizeof_rnode;


    cache_udata.f = f;
    cache_udata.type = type;
    cache_udata.rc_shared = rc_shared;
    if(NULL == (bt = (H5B_t *)H5AC_protect(f, dxpl_id, H5AC_BT, addr, &cache_udata, H5AC_READ)))
	HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "unable to load B-tree node")


    left_child = bt->child[0];
    next_addr = bt->right;
    level = bt->level;


    info_udata->bt_info->size += sizeof_rnode;
    info_udata->bt_info->num_nodes++;


    if(H5AC_unprotect(f, dxpl_id, H5AC_BT, addr, bt, H5AC__NO_FLAGS_SET) < 0)
        HGOTO_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree node")
    bt = NULL;


    while(H5F_addr_defined(next_addr)) {

        addr = next_addr;
        if(NULL == (bt = (H5B_t *)H5AC_protect(f, dxpl_id, H5AC_BT, addr, &cache_udata, H5AC_READ)))
            HGOTO_ERROR(H5E_BTREE, H5E_CANTPROTECT, FAIL, "B-tree node")


        next_addr = bt->right;


        info_udata->bt_info->size += sizeof_rnode;
        info_udata->bt_info->num_nodes++;


        if(H5AC_unprotect(f, dxpl_id, H5AC_BT, addr, bt, H5AC__NO_FLAGS_SET) < 0)
            HGOTO_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree node")
        bt = NULL;
    }


    if(level > 0) {

	if(H5B_get_info_helper(f, dxpl_id, type, left_child, info_udata) < 0)
	    HGOTO_ERROR(H5E_BTREE, H5E_CANTLIST, FAIL, "unable to list B-tree node")
    }

done:
    if(bt && H5AC_unprotect(f, dxpl_id, H5AC_BT, addr, bt, H5AC__NO_FLAGS_SET) < 0)
        HDONE_ERROR(H5E_BTREE, H5E_CANTUNPROTECT, FAIL, "unable to release B-tree node")

    FUNC_LEAVE_NOAPI(ret_value)
}
