ws_bc_data_free(unsigned char *data)
{
    size_t len = WS_MB_UINT32_MAX_ENCODED_LEN;

    if (data == NULL)
        return;


    (void) ws_decode_mb_uint32(data + 1, &len);


    ws_free(data - (WS_MB_UINT32_MAX_ENCODED_LEN - len));
}
