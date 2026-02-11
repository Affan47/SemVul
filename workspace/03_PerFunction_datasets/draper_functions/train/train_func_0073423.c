H5D__compound_opt_write(size_t nelmts, const H5D_type_info_t *type_info)
{
    uint8_t    *xsbuf, *xdbuf;
    size_t     src_stride, dst_stride;
    size_t     i;

    FUNC_ENTER_STATIC_NOERR


    HDassert(nelmts > 0);
    HDassert(type_info);


    src_stride = type_info->src_type_size;
    dst_stride = type_info->dst_type_size;


    xsbuf = (uint8_t *)type_info->tconv_buf;
    xdbuf = (uint8_t *)type_info->tconv_buf;
    for(i = 0; i < nelmts; i++) {
        HDmemmove(xdbuf, xsbuf, dst_stride);


        xsbuf += src_stride;
        xdbuf += dst_stride;
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
