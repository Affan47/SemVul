H5D__gather_file(const H5D_io_info_t *_io_info,
    const H5S_t *space, H5S_sel_iter_t *iter, size_t nelmts,
    void *_buf)
{
    H5D_io_info_t tmp_io_info;
    hsize_t _off[H5D_IO_VECTOR_SIZE];
    hsize_t *off = NULL;
    hsize_t mem_off;
    size_t mem_curr_seq;
    size_t dset_curr_seq;
    size_t _len[H5D_IO_VECTOR_SIZE];
    size_t *len = NULL;
    size_t orig_mem_len, mem_len;
    size_t nseq;
    size_t nelem;
    size_t ret_value = nelmts;

    FUNC_ENTER_STATIC


    HDassert(_io_info);
    HDassert(_io_info->dset);
    HDassert(_io_info->store);
    HDassert(space);
    HDassert(iter);
    HDassert(nelmts > 0);
    HDassert(_buf);


    HDmemcpy(&tmp_io_info, _io_info, sizeof(*_io_info));
    tmp_io_info.op_type = H5D_IO_OP_READ;
    tmp_io_info.u.rbuf = _buf;


    if(tmp_io_info.dxpl_cache->vec_size > H5D_IO_VECTOR_SIZE) {
        if(NULL == (len = H5FL_SEQ_MALLOC(size_t, tmp_io_info.dxpl_cache->vec_size)))
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, 0, "can't allocate I/O length vector array")
        if(NULL == (off = H5FL_SEQ_MALLOC(hsize_t, tmp_io_info.dxpl_cache->vec_size)))
            HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, 0, "can't allocate I/O offset vector array")
    }
    else {
        len = _len;
        off = _off;
    }


    while(nelmts > 0) {

        if(H5S_SELECT_GET_SEQ_LIST(space, H5S_GET_SEQ_LIST_SORTED, iter, tmp_io_info.dxpl_cache->vec_size, nelmts, &nseq, &nelem, off, len) < 0)
            HGOTO_ERROR(H5E_INTERNAL, H5E_UNSUPPORTED, 0, "sequence length generation failed")


        mem_curr_seq = dset_curr_seq = 0;
        orig_mem_len = mem_len = nelem * iter->elmt_size;
        mem_off = 0;


        if((*tmp_io_info.layout_ops.readvv)(&tmp_io_info, nseq, &dset_curr_seq,
                len, off, (size_t)1, &mem_curr_seq, &mem_len, &mem_off) < 0)
            HGOTO_ERROR(H5E_DATASPACE, H5E_READERROR, 0, "read error")


        tmp_io_info.u.rbuf = (uint8_t *)tmp_io_info.u.rbuf + orig_mem_len;


        nelmts -= nelem;
    }

done:

    if(len && len != _len)
        len = H5FL_SEQ_FREE(size_t, len);
    if(off && off != _off)
        off = H5FL_SEQ_FREE(hsize_t, off);

    FUNC_LEAVE_NOAPI(ret_value)
}
