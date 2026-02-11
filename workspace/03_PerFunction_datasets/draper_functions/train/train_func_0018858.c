H5O_pline_pre_copy_file(H5F_t UNUSED *file_src, const void *mesg_src,
    hbool_t UNUSED *deleted, const H5O_copy_t UNUSED *cpy_info, void *_udata)
{
    const H5O_pline_t *pline_src = (const H5O_pline_t *)mesg_src;
    H5O_copy_file_ud_common_t *udata = (H5O_copy_file_ud_common_t *)_udata;
    herr_t             ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5O_pline_pre_copy_file)


    HDassert(pline_src);


    if(udata)
        if(NULL == (udata->src_pline = (H5O_pline_t *)H5O_pline_copy(pline_src, NULL)))
            HGOTO_ERROR(H5E_PLINE, H5E_CANTINIT, FAIL, "unable to copy")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
