H5O_attr_pre_copy_file(H5F_t H5_ATTR_UNUSED *file_src, const void H5_ATTR_UNUSED *native_src,
    hbool_t *deleted, const H5O_copy_t *cpy_info, void H5_ATTR_UNUSED *udata)
{
    FUNC_ENTER_NOAPI_NOINIT_NOERR


    HDassert(deleted);
    HDassert(cpy_info);


    if(cpy_info->copy_without_attr)
        *deleted = TRUE;

    FUNC_LEAVE_NOAPI(SUCCEED)
}
