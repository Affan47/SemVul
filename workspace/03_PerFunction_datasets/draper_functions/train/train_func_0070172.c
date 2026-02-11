H5HF_man_iblock_dest(H5HF_indirect_t *iblock)
{
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(iblock);
    HDassert(iblock->rc == 0);


    HDassert(iblock->hdr);
    if(H5HF_hdr_decr(iblock->hdr) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTDEC, FAIL, "can't decrement reference count on shared heap header")
    if(iblock->parent)
        if(H5HF_iblock_decr(iblock->parent) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTDEC, FAIL, "can't decrement reference count on shared indirect block")


    if(iblock->ents)
        iblock->ents = H5FL_SEQ_FREE(H5HF_indirect_ent_t, iblock->ents);
    if(iblock->filt_ents)
        iblock->filt_ents = H5FL_SEQ_FREE(H5HF_indirect_filt_ent_t, iblock->filt_ents);
    if(iblock->child_iblocks)
        iblock->child_iblocks = H5FL_SEQ_FREE(H5HF_indirect_ptr_t, iblock->child_iblocks);


    iblock = H5FL_FREE(H5HF_indirect_t, iblock);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
