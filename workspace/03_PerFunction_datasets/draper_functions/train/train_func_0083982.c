H5SM_read_mesg_fh_cb(const void *obj, size_t obj_len, void *_udata)
{
    H5SM_read_udata_t *udata = (H5SM_read_udata_t *)_udata;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    if(NULL == (udata->encoding_buf = H5MM_malloc(obj_len)))
        HGOTO_ERROR(H5E_SOHM, H5E_NOSPACE, FAIL, "memory allocation failed")


    HDmemcpy(udata->encoding_buf, obj, obj_len);
    udata->buf_size = obj_len;

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
