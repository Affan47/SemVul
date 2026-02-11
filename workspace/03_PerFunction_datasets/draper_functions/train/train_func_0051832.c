H5T_vlen_disk_write(H5F_t *f, hid_t dxpl_id, const H5T_vlen_alloc_info_t H5_ATTR_UNUSED *vl_alloc_info,
    void *_vl, void *buf, void *_bg, size_t seq_len, size_t base_size)
{
    uint8_t *vl = (uint8_t *)_vl;
    uint8_t *bg = (uint8_t *)_bg;
    H5HG_t hobjid;
    size_t len;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(vl);
    HDassert(seq_len == 0 || buf);
    HDassert(f);


    if(bg!=NULL) {
        H5HG_t bg_hobjid;


        bg += 4;


        H5F_addr_decode(f, (const uint8_t **)&bg, &(bg_hobjid.addr));
        UINT32DECODE(bg, bg_hobjid.idx);


        if(bg_hobjid.addr > 0) {

            if(H5HG_remove(f, dxpl_id, &bg_hobjid) < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_WRITEERROR, FAIL, "Unable to remove heap object")
        }
    }


    UINT32ENCODE(vl, seq_len);


    len = (seq_len*base_size);
    if(H5HG_insert(f, dxpl_id, len, buf, &hobjid) < 0)
        HGOTO_ERROR(H5E_DATATYPE, H5E_WRITEERROR, FAIL, "Unable to write VL information")


    H5F_addr_encode(f, &vl, hobjid.addr);
    UINT32ENCODE(vl, hobjid.idx);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
