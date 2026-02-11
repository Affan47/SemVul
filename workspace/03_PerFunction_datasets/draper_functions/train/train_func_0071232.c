H5HF_space_start(H5HF_hdr_t *hdr, hid_t dxpl_id, hbool_t may_create)
{
    const H5FS_section_class_t *classes[] = {
        H5HF_FSPACE_SECT_CLS_SINGLE,
        H5HF_FSPACE_SECT_CLS_FIRST_ROW,
        H5HF_FSPACE_SECT_CLS_NORMAL_ROW,
        H5HF_FSPACE_SECT_CLS_INDIRECT};
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(hdr);


    if(H5F_addr_defined(hdr->fs_addr)) {

        if(NULL == (hdr->fspace = H5FS_open(hdr->f, dxpl_id, hdr->fs_addr,
                NELMTS(classes), classes, hdr, H5HF_FSPACE_THRHD_DEF, H5HF_FSPACE_ALIGN_DEF)))
            HGOTO_ERROR(H5E_HEAP, H5E_CANTINIT, FAIL, "can't initialize free space info")
    }
    else {

        if(may_create) {
            H5FS_create_t fs_create;


            fs_create.client = H5FS_CLIENT_FHEAP_ID;
            fs_create.shrink_percent = H5HF_FSPACE_SHRINK;
            fs_create.expand_percent = H5HF_FSPACE_EXPAND;
            fs_create.max_sect_size = hdr->man_dtable.cparam.max_direct_size;
            fs_create.max_sect_addr = hdr->man_dtable.cparam.max_index;


            if(NULL == (hdr->fspace = H5FS_create(hdr->f, dxpl_id, &hdr->fs_addr,
                    &fs_create, NELMTS(classes), classes, hdr, H5HF_FSPACE_THRHD_DEF, H5HF_FSPACE_ALIGN_DEF)))
                HGOTO_ERROR(H5E_HEAP, H5E_CANTINIT, FAIL, "can't initialize free space info")
            HDassert(H5F_addr_defined(hdr->fs_addr));
        }
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
