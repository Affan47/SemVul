H5HL_heapsize(H5F_t *f, hid_t dxpl_id, haddr_t addr, hsize_t *heap_size)
{
    H5HL_cache_prfx_ud_t prfx_udata;
    H5HL_prfx_t *prfx = NULL;
    H5HL_t *heap;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5HL_heapsize, FAIL)


    HDassert(f);
    HDassert(H5F_addr_defined(addr));
    HDassert(heap_size);


    prfx_udata.sizeof_size = H5F_SIZEOF_SIZE(f);
    prfx_udata.sizeof_addr = H5F_SIZEOF_ADDR(f);
    prfx_udata.prfx_addr = addr;
    prfx_udata.sizeof_prfx = H5HL_SIZEOF_HDR(f);
    prfx_udata.loaded = FALSE;
    prfx_udata.free_block = H5HL_FREE_NULL;


    if(NULL == (prfx = (H5HL_prfx_t *)H5AC_protect(f, dxpl_id, H5AC_LHEAP_PRFX, addr, &prfx_udata, H5AC_READ)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTPROTECT, FAIL, "unable to load heap prefix")


    heap = prfx->heap;


    *heap_size += (hsize_t)(heap->prfx_size + heap->dblk_size);

done:
    if(prfx && H5AC_unprotect(f, dxpl_id, H5AC_LHEAP_PRFX, heap->prfx_addr, prfx, H5AC__NO_FLAGS_SET) < 0)
        HDONE_ERROR(H5E_HEAP, H5E_CANTUNPROTECT, FAIL, "unable to release local heap prefix")

    FUNC_LEAVE_NOAPI(ret_value)
}
