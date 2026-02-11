H5HF_man_dblock_destroy(H5HF_hdr_t *hdr, hid_t dxpl_id, H5HF_direct_t *dblock,
    haddr_t dblock_addr)
{
    hsize_t dblock_size;
    unsigned cache_flags = H5AC__NO_FLAGS_SET;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5HF_man_dblock_destroy)


    HDassert(hdr);
    HDassert(dblock);


    if(hdr->filter_len > 0) {

        if(dblock->parent == NULL)

            dblock_size = (hsize_t)hdr->pline_root_direct_size;
        else {
            H5HF_indirect_t *par_iblock;
            unsigned par_entry;


            par_iblock = dblock->parent;
            par_entry = dblock->par_entry;


            dblock_size = (hsize_t)par_iblock->filt_ents[par_entry].size;
        }
    }
    else
        dblock_size = (hsize_t)dblock->size;


    if(hdr->man_dtable.curr_root_rows == 0) {

        HDassert(hdr->man_dtable.table_addr == dblock_addr);
        HDassert(hdr->man_dtable.cparam.start_block_size == dblock->size);


        HDassert(!H5HF_man_iter_ready(&hdr->next_block));


        hdr->man_dtable.table_addr = HADDR_UNDEF;


        if(H5HF_hdr_empty(hdr) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTSHRINK, FAIL, "can't make heap empty")
    }
    else {

        hdr->man_alloc_size -= dblock->size;


        if((dblock->block_off + dblock->size) == hdr->man_iter_off) {

            if(H5HF_hdr_reverse_iter(hdr, dxpl_id, dblock_addr) < 0)
                HGOTO_ERROR(H5E_HEAP, H5E_CANTRELEASE, FAIL, "can't reverse 'next block' iterator")
        }
#if 0
        else {
            unsigned par_row, par_col;


            par_row = dblock->par_entry / hdr->man_dtable.cparam.width;
            par_col = dblock->par_entry % hdr->man_dtable.cparam.width;


            if(H5HF_sect_range_add(hdr, dxpl_id, dblock->block_off, hdr->man_dtable.row_tot_dblock_free[par_row],
                    dblock->parent, par_row, par_col, 1) < 0)
                HGOTO_ERROR(H5E_HEAP, H5E_CANTINSERT, FAIL, "can't create range section for direct block being destroyed")
        }
#endif


        if(dblock->parent) {
            if(H5HF_man_iblock_detach(dblock->parent, dxpl_id, dblock->par_entry) < 0)
                HGOTO_ERROR(H5E_HEAP, H5E_CANTATTACH, FAIL, "can't detach from parent indirect block");
            dblock->parent = NULL;
            dblock->par_entry = 0;
        }
    }


    dblock->file_size = dblock_size;
    cache_flags |= H5AC__DIRTIED_FLAG | H5AC__DELETED_FLAG | H5AC__FREE_FILE_SPACE_FLAG;

done:

    if(H5AC_unprotect(hdr->f, dxpl_id, H5AC_FHEAP_DBLOCK, dblock_addr, dblock, cache_flags) < 0)
        HDONE_ERROR(H5E_HEAP, H5E_CANTUNPROTECT, FAIL, "unable to release fractal heap direct block")

    FUNC_LEAVE_NOAPI(ret_value)
}
