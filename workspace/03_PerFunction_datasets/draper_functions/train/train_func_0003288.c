flv_append_data( flv_buffer *c, uint8_t *data, unsigned size )
{
    unsigned ns = c->d_cur + size;

    if( ns > c->d_max )
    {
        void *dp;
        unsigned dn = 16;
        while( ns > dn )
            dn <<= 1;

        dp = realloc( c->data, dn );
        if( !dp )
            return -1;

        c->data = dp;
        c->d_max = dn;
    }

    memcpy( c->data + c->d_cur, data, size );

    c->d_cur = ns;

    return 0;
}
