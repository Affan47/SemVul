H5HF_get_cparam_test(const H5HF_t *fh, H5HF_create_t *cparam)
{
    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(fh);
    HDassert(cparam);


    if(fh->hdr->id_len == (unsigned)(1 + fh->hdr->heap_off_size + fh->hdr->heap_len_size))
        cparam->id_len = 0;
    else if(fh->hdr->id_len == (1 + fh->hdr->sizeof_size + fh->hdr->sizeof_addr))
        cparam->id_len = 1;
    else
        cparam->id_len = fh->hdr->id_len;
    cparam->max_man_size = fh->hdr->max_man_size;
    HDmemcpy(&(cparam->managed), &(fh->hdr->man_dtable.cparam), sizeof(H5HF_dtable_cparam_t));
    H5O_msg_copy(H5O_PLINE_ID, &(fh->hdr->pline), &(cparam->pline));

    FUNC_LEAVE_NOAPI(SUCCEED)
}
