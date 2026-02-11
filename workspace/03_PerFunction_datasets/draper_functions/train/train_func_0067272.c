H5HF_sect_single_merge(H5FS_section_info_t *_sect1, H5FS_section_info_t *_sect2,
    void *_udata)
{
    H5HF_free_section_t *sect1 = (H5HF_free_section_t *)_sect1;
    H5HF_free_section_t *sect2 = (H5HF_free_section_t *)_sect2;
    H5HF_sect_add_ud_t *udata = (H5HF_sect_add_ud_t *)_udata;
    H5HF_hdr_t *hdr = udata->hdr;
    hid_t dxpl_id = udata->dxpl_id;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(sect1);
    HDassert(sect1->sect_info.type == H5HF_FSPACE_SECT_SINGLE);
    HDassert(sect2);
    HDassert(sect2->sect_info.type == H5HF_FSPACE_SECT_SINGLE);
    HDassert(H5F_addr_eq(sect1->sect_info.addr + sect1->sect_info.size, sect2->sect_info.addr));


    sect1->sect_info.size += sect2->sect_info.size;


    if(H5HF_sect_single_free((H5FS_section_info_t *)sect2) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTRELEASE, FAIL, "can't free section node")


    if(sect1->sect_info.state != H5FS_SECT_LIVE)
        if(H5HF_sect_single_revive(hdr, dxpl_id, sect1) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTINIT, FAIL, "can't revive single free section")


    if(H5HF_sect_single_full_dblock(hdr, dxpl_id, sect1) < 0)
        HGOTO_ERROR(H5E_HEAP, H5E_CANTCONVERT, FAIL, "can't check/convert single section")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
