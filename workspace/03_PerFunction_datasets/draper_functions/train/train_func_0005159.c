syck_emitter_escape( SyckEmitter *e, const char *src, long len )
{
    int i;
    for( i = 0; i < len; i++ )
    {
        if( (src[i] < 0x20) || (0x7E < src[i]) )
        {
            syck_emitter_write( e, "\\", 1 );
            if( '\0' == src[i] )
                syck_emitter_write( e, "0", 1 );
            else
            {
                syck_emitter_write( e, "x", 1 );
                syck_emitter_write( e, (const char *)hex_table + ((src[i] & 0xF0) >> 4), 1 );
                syck_emitter_write( e, (const char *)hex_table + (src[i] & 0x0F), 1 );
            }
        }
        else
        {
            syck_emitter_write( e, src + i, 1 );
            if( '\\' == src[i] )
                syck_emitter_write( e, "\\", 1 );
        }
    }
}
