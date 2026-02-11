H5_checksum_crc_make_table(void)
{
    uint32_t c;
    unsigned n, k;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5_checksum_crc_make_table)


    for(n = 0; n < 256; n++) {
        c = (uint32_t) n;
        for(k = 0; k < 8; k++)
            if(c & 1)
                c = H5_CRC_QUOTIENT ^ (c >> 1);
            else
                c = c >> 1;
        H5_crc_table[n] = c;
    }
    H5_crc_table_computed = TRUE;

    FUNC_LEAVE_NOAPI_VOID
}
