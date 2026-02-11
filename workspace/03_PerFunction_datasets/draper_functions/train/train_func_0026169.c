H5HF_sect_row_deserialize(const H5FS_section_class_t *cls, hid_t dxpl_id,
    const uint8_t *buf, haddr_t sect_addr, hsize_t sect_size,
    unsigned *des_flags)
{
    H5HF_hdr_t *hdr;
    H5FS_section_info_t *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(cls);
    HDassert(buf);
    HDassert(H5F_addr_defined(sect_addr));
    HDassert(sect_size);


    hdr = ((H5HF_sect_private_t *)(cls->cls_private))->hdr;
    if(NULL ==  (ret_value = H5HF_sect_indirect_deserialize(hdr, dxpl_id, buf,
            sect_addr, sect_size, des_flags)))
        HGOTO_ERROR(H5E_HEAP, H5E_CANTDECODE, NULL, "can't deserialize row section's underlying indirect section")

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
