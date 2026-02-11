H5T_vlen_disk_setnull(H5F_t *f, hid_t dxpl_id, void *_vl, void *_bg)
{
    uint8_t *vl = (uint8_t *)_vl;
    uint8_t *bg = (uint8_t *)_bg;
    uint32_t seq_len = 0;
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(f);
    HDassert(vl);


    if(bg != NULL) {
        H5HG_t bg_hobjid;


        bg += 4;


        H5F_addr_decode(f, (const uint8_t **)&bg, &(bg_hobjid.addr));
        INT32DECODE(bg, bg_hobjid.idx);


        if(bg_hobjid.addr > 0) {

            if(H5HG_remove(f, dxpl_id, &bg_hobjid) < 0)
                HGOTO_ERROR(H5E_DATATYPE, H5E_WRITEERROR, FAIL, "Unable to remove heap object")
         }
    }


    UINT32ENCODE(vl, seq_len);


    H5F_addr_encode(f, &vl, (haddr_t)0);
    INT32ENCODE(vl, 0);

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
