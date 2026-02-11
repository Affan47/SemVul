H5O_cache_chk_load(H5F_t *f, hid_t dxpl_id, haddr_t addr, void *_udata)
{
    H5O_chunk_proxy_t	*chk_proxy = NULL;
    H5O_chk_cache_ud_t *udata = (H5O_chk_cache_ud_t *)_udata;
    H5WB_t      *wb = NULL;
    uint8_t     chunk_buf[H5O_SPEC_READ_SIZE];
    uint8_t     *buf;
    H5O_chunk_proxy_t	*ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(H5F_addr_defined(addr));
    HDassert(udata);
    HDassert(udata->oh);


    if(NULL == (chk_proxy = H5FL_CALLOC(H5O_chunk_proxy_t)))
	HGOTO_ERROR(H5E_OHDR, H5E_CANTALLOC, NULL, "memory allocation failed")


    if(NULL == (wb = H5WB_wrap(chunk_buf, sizeof(chunk_buf))))
        HGOTO_ERROR(H5E_OHDR, H5E_CANTINIT, NULL, "can't wrap buffer")


    if(NULL == (buf = (uint8_t *)H5WB_actual(wb, udata->size)))
        HGOTO_ERROR(H5E_OHDR, H5E_NOSPACE, NULL, "can't get actual buffer")


    if(H5F_block_read(f, H5FD_MEM_OHDR, addr, udata->size, dxpl_id, buf) < 0)
        HGOTO_ERROR(H5E_OHDR, H5E_READERROR, NULL, "unable to read object header continuation chunk")


    if(udata->decoding) {

        HDassert(udata->common.f);
        HDassert(udata->common.cont_msg_info);


        if(H5O_chunk_deserialize(udata->oh, udata->common.addr, udata->size, buf, &(udata->common), &chk_proxy->cache_info.is_dirty) < 0)
            HGOTO_ERROR(H5E_OHDR, H5E_CANTINIT, NULL, "can't deserialize object header chunk")


        chk_proxy->oh = udata->oh;
        chk_proxy->chunkno = udata->oh->nchunks - 1;
    }
    else {

        HDassert(udata->chunkno < udata->oh->nchunks);


        chk_proxy->oh = udata->oh;
        chk_proxy->chunkno = udata->chunkno;


        HDassert(0 == HDmemcmp(buf, chk_proxy->oh->chunk[chk_proxy->chunkno].image, chk_proxy->oh->chunk[chk_proxy->chunkno].size));
    }


    if(H5O_inc_rc(udata->oh) < 0)
        HGOTO_ERROR(H5E_OHDR, H5E_CANTINC, NULL, "can't increment reference count on object header")


    ret_value = chk_proxy;

done:

    if(wb && H5WB_unwrap(wb) < 0)
        HDONE_ERROR(H5E_OHDR, H5E_CLOSEERROR, NULL, "can't close wrapped buffer")


    if(!ret_value && chk_proxy)
        if(H5O_chunk_proxy_dest(chk_proxy) < 0)
	    HDONE_ERROR(H5E_OHDR, H5E_CANTRELEASE, NULL, "unable to destroy object header chunk proxy")

    FUNC_LEAVE_NOAPI(ret_value)
}
