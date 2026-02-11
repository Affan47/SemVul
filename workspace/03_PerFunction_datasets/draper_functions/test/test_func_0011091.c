H5HF_huge_bt2_crt_dbg_context(H5F_t *f, hid_t UNUSED dxpl_id, haddr_t UNUSED addr)
{
    H5HF_huge_bt2_ctx_t *ctx;
    void *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);


    if(NULL == (ctx = H5FL_MALLOC(H5HF_huge_bt2_ctx_t)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTALLOC, NULL, "can't allocate callback context")


    ctx->sizeof_addr = H5F_SIZEOF_ADDR(f);
    ctx->sizeof_size = H5F_SIZEOF_SIZE(f);


    ret_value = ctx;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
