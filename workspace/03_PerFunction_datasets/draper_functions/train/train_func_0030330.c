H5SM_create_index(H5F_t *f, H5SM_index_header_t *header, hid_t dxpl_id)
{
    H5HF_create_t fheap_cparam;
    H5HF_t *fheap = NULL;
    H5B2_t *bt2 = NULL;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(header);
    HDassert(header->index_addr == HADDR_UNDEF);
    HDassert(header->btree_min <= header->list_max + 1);


    if(header->list_max > 0) {
        haddr_t list_addr = HADDR_UNDEF;


        if((list_addr = H5SM_create_list(f, header, dxpl_id)) == HADDR_UNDEF)
            HGOTO_ERROR(H5E_SOHM, H5E_CANTCREATE, FAIL, "list creation failed for SOHM index")


        header->index_type = H5SM_LIST;
        header->index_addr = list_addr;
    }

    else {
        H5B2_create_t bt2_cparam;
        haddr_t tree_addr = HADDR_UNDEF;


        bt2_cparam.cls = H5SM_INDEX;
        bt2_cparam.node_size = (uint32_t)H5SM_B2_NODE_SIZE;
        bt2_cparam.rrec_size = (uint32_t)H5SM_SOHM_ENTRY_SIZE(f);
        bt2_cparam.split_percent = H5SM_B2_SPLIT_PERCENT;
        bt2_cparam.merge_percent = H5SM_B2_MERGE_PERCENT;
        if(NULL == (bt2 = H5B2_create(f, dxpl_id, &bt2_cparam, f)))
            HGOTO_ERROR(H5E_SOHM, H5E_CANTCREATE, FAIL, "B-tree creation failed for SOHM index")


        if(H5B2_get_addr(bt2, &tree_addr) < 0)
            HGOTO_ERROR(H5E_SOHM, H5E_CANTGET, FAIL, "can't get v2 B-tree address for SOHM index")


        header->index_type = H5SM_BTREE;
        header->index_addr = tree_addr;
    }


    HDmemset(&fheap_cparam, 0, sizeof(fheap_cparam));
    fheap_cparam.managed.width = H5O_FHEAP_MAN_WIDTH;
    fheap_cparam.managed.start_block_size = H5O_FHEAP_MAN_START_BLOCK_SIZE;
    fheap_cparam.managed.max_direct_size = H5O_FHEAP_MAN_MAX_DIRECT_SIZE;
    fheap_cparam.managed.max_index = H5O_FHEAP_MAN_MAX_INDEX;
    fheap_cparam.managed.start_root_rows = H5O_FHEAP_MAN_START_ROOT_ROWS;
    fheap_cparam.checksum_dblocks = H5O_FHEAP_CHECKSUM_DBLOCKS;
    fheap_cparam.id_len = 0;
    fheap_cparam.max_man_size = H5O_FHEAP_MAX_MAN_SIZE;
    if(NULL == (fheap = H5HF_create(f, dxpl_id, &fheap_cparam)))
        HGOTO_ERROR(H5E_SOHM, H5E_CANTINIT, FAIL, "unable to create fractal heap")

    if(H5HF_get_heap_addr(fheap, &(header->heap_addr)) < 0)
        HGOTO_ERROR(H5E_SOHM, H5E_CANTGETSIZE, FAIL, "can't get fractal heap address")

#ifndef NDEBUG
{
    size_t fheap_id_len;


    if(H5HF_get_id_len(fheap, &fheap_id_len) < 0)
        HGOTO_ERROR(H5E_SOHM, H5E_CANTGETSIZE, FAIL, "can't get fractal heap ID length")
    HDassert(fheap_id_len == H5O_FHEAP_ID_LEN);
}
#endif

done:

    if(fheap && H5HF_close(fheap, dxpl_id) < 0)
        HDONE_ERROR(H5E_SOHM, H5E_CANTCLOSEOBJ, FAIL, "can't close fractal heap")
    if(bt2 && H5B2_close(bt2, dxpl_id) < 0)
        HDONE_ERROR(H5E_SOHM, H5E_CANTCLOSEOBJ, FAIL, "can't close v2 B-tree for SOHM index")

    FUNC_LEAVE_NOAPI(ret_value)
}
