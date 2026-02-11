H5O_dtype_pre_copy_file(H5F_t *file_src, const void *mesg_src,
    hbool_t H5_ATTR_UNUSED *deleted, const H5O_copy_t H5_ATTR_UNUSED *cpy_info,
    void *_udata)
{
    const H5T_t	*dt_src = (const H5T_t *)mesg_src;
    H5D_copy_file_ud_t *udata = (H5D_copy_file_ud_t *)_udata;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(file_src);
    HDassert(dt_src);


    if(udata) {

        if(NULL == (udata->src_dtype = H5T_copy(dt_src, H5T_COPY_TRANSIENT)))
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "unable to copy")


        if(H5T_set_loc(udata->src_dtype, file_src, H5T_LOC_DISK) < 0)
            HGOTO_ERROR(H5E_DATATYPE, H5E_CANTINIT, FAIL, "cannot mark datatype on disk")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
