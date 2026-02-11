H5P_iterate_pclass(const H5P_genclass_t *pclass, int *idx,
    H5P_iterate_int_t cb_func, void *udata)
{
    H5P_iter_pclass_ud_t udata_int;
    int curr_idx = 0;
    int ret_value = 0;

    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(pclass);
    HDassert(idx);
    HDassert(cb_func);


    udata_int.cb_func = cb_func;
    udata_int.udata = udata;
    udata_int.curr_idx_ptr = &curr_idx;
    udata_int.prev_idx = *idx;


    ret_value = H5SL_iterate(pclass->props, H5P__iterate_pclass_cb, &udata_int);
    if(ret_value != 0)
        HGOTO_DONE(ret_value);

done:

    *idx = curr_idx;

    FUNC_LEAVE_NOAPI(ret_value)
}
