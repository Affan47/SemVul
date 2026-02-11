H5O_link_post_copy_file(const H5O_loc_t *src_oloc, const void *mesg_src,
    H5O_loc_t *dst_oloc, void *mesg_dst, hid_t dxpl_id, H5O_copy_t *cpy_info)
{
    const H5O_link_t    *link_src = (const H5O_link_t *)mesg_src;
    H5O_link_t          *link_dst = (H5O_link_t *)mesg_dst;
    herr_t              ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5O_link_post_copy_file)


    HDassert(link_src);
    HDassert(dst_oloc);
    HDassert(H5F_addr_defined(dst_oloc->addr));
    HDassert(dst_oloc->file);
    HDassert(link_dst);
    HDassert(cpy_info);
    HDassert(cpy_info->max_depth < 0 || cpy_info->curr_depth < cpy_info->max_depth);


    if(H5G_link_copy_file(dst_oloc->file, dxpl_id, link_src, src_oloc, link_dst,
            cpy_info) < 0)
        HGOTO_ERROR(H5E_OHDR, H5E_CANTCOPY, FAIL, "unable to copy link")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
