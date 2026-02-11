H5HF_iblock_pin(H5HF_indirect_t *iblock)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(iblock);


    if(H5AC_pin_protected_entry(iblock) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTPIN, FAIL, "unable to pin fractal heap indirect block")


    if(iblock->parent) {
        H5HF_indirect_t *par_iblock = iblock->parent;
        unsigned indir_idx;


        HDassert(par_iblock->child_iblocks);
        HDassert(iblock->par_entry >= (iblock->hdr->man_dtable.max_direct_rows
                * iblock->hdr->man_dtable.cparam.width));


        indir_idx = iblock->par_entry - (iblock->hdr->man_dtable.max_direct_rows
                * iblock->hdr->man_dtable.cparam.width);


        HDassert(par_iblock->child_iblocks[indir_idx] == NULL);
        par_iblock->child_iblocks[indir_idx] = iblock;
    }
    else {

        if(iblock->block_off == 0) {

            HDassert(0 == (iblock->hdr->root_iblock_flags & H5HF_ROOT_IBLOCK_PINNED));


            if(0 == iblock->hdr->root_iblock_flags) {
                HDassert(NULL == iblock->hdr->root_iblock);
                iblock->hdr->root_iblock = iblock;
            }


            iblock->hdr->root_iblock_flags |= H5HF_ROOT_IBLOCK_PINNED;
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
