H5HF_iblock_decr(H5HF_indirect_t *iblock)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(iblock);


    iblock->rc--;


    if(iblock->rc == 0) {
        H5HF_hdr_t *hdr;
        haddr_t iblock_addr;
        hbool_t expunge_iblock = FALSE;


        hdr = iblock->hdr;
        iblock_addr = iblock->addr;

        if(iblock->nchildren == 0) {

            if(iblock->block_off == 0 && hdr->man_dtable.curr_root_rows > 0) {

                hdr->man_dtable.curr_root_rows = 0;
                hdr->man_dtable.table_addr = HADDR_UNDEF;


                if(H5HF_hdr_empty(hdr) < 0)
                    HGOTO_ERROR(H5E_HEAP, H5E_CANTSHRINK, FAIL, "can't make heap empty")
            }


            if(iblock->parent) {

                if(H5HF_man_iblock_detach(iblock->parent, H5AC_dxpl_id, iblock->par_entry) < 0)
                    HGOTO_ERROR(H5E_HEAP, H5E_CANTATTACH, FAIL, "can't detach from parent indirect block")
                iblock->parent = NULL;
                iblock->par_entry = 0;
            }


	    expunge_iblock = TRUE;
        }


        if(H5HF_iblock_unpin(iblock) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTUNPIN, FAIL, "unable to unpin fractal heap indirect block")


	if(expunge_iblock) {

            if(H5AC_expunge_entry(hdr->f, H5AC_dxpl_id, H5AC_FHEAP_IBLOCK, iblock_addr, H5AC__FREE_FILE_SPACE_FLAG) < 0)
                HGOTO_ERROR(H5E_HEAP, H5E_CANTREMOVE, FAIL, "unable to remove indirect block from cache")
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
