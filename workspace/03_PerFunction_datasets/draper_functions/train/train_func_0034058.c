H5O_ainfo_post_copy_file(const H5O_loc_t *src_oloc, const void *mesg_src,
    H5O_loc_t *dst_oloc, void *mesg_dst, unsigned UNUSED *mesg_flags,
    hid_t dxpl_id, H5O_copy_t *cpy_info)
{
    const H5O_ainfo_t *ainfo_src = (const H5O_ainfo_t *)mesg_src;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT

    HDassert(ainfo_src);

    if(H5F_addr_defined(ainfo_src->fheap_addr)) {
        if(H5A_dense_post_copy_file_all(src_oloc, ainfo_src, dst_oloc,
                (H5O_ainfo_t *)mesg_dst, dxpl_id, cpy_info) < 0)
        HGOTO_ERROR(H5E_ATTR, H5E_CANTCOPY, FAIL, "can't copy attribute")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
