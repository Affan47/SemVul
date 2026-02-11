pdf_fontfile_hash(void *pfd)
{
    pdf_font_descriptor_t *fd = (pdf_font_descriptor_t *)pfd;
    cos_dict_t *pcd;

    if (fd->base_font && fd->base_font->FontFile) {
        pcd = (cos_dict_t *)fd->base_font->FontFile;
        if (pcd->stream_md5_valid)
            return ((char *)pcd->stream_hash);
        else
            return 0;
    } else
        return 0;
}
