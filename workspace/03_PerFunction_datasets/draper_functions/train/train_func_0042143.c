H5HF_hdr_incr(H5HF_hdr_t *hdr)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(hdr);


    if(hdr->rc == 0)
        if(H5AC_pin_protected_entry(hdr) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTPIN, FAIL, "unable to pin fractal heap header")


    hdr->rc++;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
