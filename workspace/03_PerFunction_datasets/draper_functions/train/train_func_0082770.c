H5SM_convert_btree_to_list(H5F_t * f, H5SM_index_header_t * header, hid_t dxpl_id)
{
    H5SM_list_t     *list = NULL;
    H5SM_list_cache_ud_t cache_udata;
    haddr_t          btree_addr;
    herr_t           ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    btree_addr = header->index_addr;

    header->num_messages = 0;
    header->index_type = H5SM_LIST;


    if(HADDR_UNDEF == (header->index_addr = H5SM_create_list(f, header, dxpl_id)))
        HGOTO_ERROR(H5E_SOHM, H5E_CANTINIT, FAIL, "unable to create shared message list")


    cache_udata.f = f;
    cache_udata.header = header;


    if(NULL == (list = (H5SM_list_t *)H5AC_protect(f, dxpl_id, H5AC_SOHM_LIST, header->index_addr, &cache_udata, H5AC_WRITE)))
        HGOTO_ERROR(H5E_SOHM, H5E_CANTPROTECT, FAIL, "unable to load SOHM list index")


    if(H5B2_delete(f, dxpl_id, btree_addr, f, H5SM_bt2_convert_to_list_op, list) < 0)
        HGOTO_ERROR(H5E_SOHM, H5E_CANTDELETE, FAIL, "unable to delete B-tree")

done:

    if(list && H5AC_unprotect(f, dxpl_id, H5AC_SOHM_LIST, header->index_addr, list, H5AC__DIRTIED_FLAG) < 0)
        HDONE_ERROR(H5E_SOHM, H5E_CANTUNPROTECT, FAIL, "unable to unprotect SOHM index")

    FUNC_LEAVE_NOAPI(ret_value)
}
