H5S_hyper_span_precompute(H5S_hyper_span_info_t *spans, size_t elmt_size)
{
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(spans);


    if(H5S_hyper_span_precompute_helper(spans, elmt_size) < 0)
        HGOTO_ERROR(H5E_INTERNAL, H5E_CANTFREE, FAIL, "can't precompute span info")


    H5S_hyper_span_scratch(spans, NULL);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
