H5O_link_copy_file(H5F_t H5_ATTR_UNUSED *file_src, void *native_src, H5F_t H5_ATTR_UNUSED *file_dst,
    hbool_t H5_ATTR_UNUSED *recompute_size, unsigned H5_ATTR_UNUSED *mesg_flags,
    H5O_copy_t H5_ATTR_UNUSED *cpy_info, void H5_ATTR_UNUSED *udata, hid_t H5_ATTR_UNUSED dxpl_id)
{
    H5O_link_t  *link_src = (H5O_link_t *)native_src;
    void        *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(link_src);
    HDassert(cpy_info);
    HDassert(cpy_info->max_depth < 0 || cpy_info->curr_depth < cpy_info->max_depth);


    if(link_src->type > H5L_TYPE_SOFT && link_src->type < H5L_TYPE_UD_MIN)
        HGOTO_ERROR(H5E_SYM, H5E_BADVALUE, NULL, "unrecognized built-in link type")


    if(NULL == (ret_value = H5FL_CALLOC(H5O_link_t)))
	HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
