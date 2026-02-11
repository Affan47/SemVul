calc_crc( unsigned char * buf, int len)
{
    unsigned long crc = 0xFFFFFFFF;

    for( ; len > 0; len--, buf++ )
        crc = crc_tbl[(crc ^ *buf) & 0xFF] ^ ( crc >> 8 );

    return( ~crc );
}
