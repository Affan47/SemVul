H5HF_man_iblock_alloc_row(H5HF_hdr_t *hdr, hid_t dxpl_id, H5HF_free_section_t **sec_node)
{
    H5HF_indirect_t *iblock = NULL;
    H5HF_free_section_t *old_sec_node = *sec_node;
    unsigned dblock_entry;
    hbool_t iblock_held = FALSE;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(hdr);
    HDassert(sec_node && old_sec_node);
    HDassert(old_sec_node->u.row.row < hdr->man_dtable.max_direct_rows);


    if(old_sec_node->sect_info.state == H5FS_SECT_SERIALIZED) {

        if(H5HF_sect_row_revive(hdr, dxpl_id, old_sec_node) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTREVIVE, FAIL, "can't revive indirect section")
    }


    if(NULL == (iblock = H5HF_sect_row_get_iblock(old_sec_node)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTGET, FAIL, "can't retrieve indirect block for row section")


    if(H5HF_iblock_incr(iblock) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTINC, FAIL, "can't increment reference count on shared indirect block")
    iblock_held = TRUE;


    if(H5HF_sect_row_reduce(hdr, dxpl_id, old_sec_node, &dblock_entry) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTSHRINK, FAIL, "can't reduce row section node")


    if(H5HF_man_dblock_create(dxpl_id, hdr, iblock, dblock_entry, NULL, sec_node) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTALLOC, FAIL, "can't allocate fractal heap direct block")

done:

    if(iblock_held)
        if(H5HF_iblock_decr(iblock) < 0)
            HDONE_ERROR(H5E_HEAP, H5E_CANTDEC, FAIL, "can't decrement reference count on shared indirect block")

    FUNC_LEAVE_NOAPI(ret_value)
}
