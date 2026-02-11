write_headers( hnd_t handle, x264_nal_t *p_nal )
{
    flv_hnd_t *p_flv = handle;
    flv_buffer *c = p_flv->c;

    int sps_size = p_nal[0].i_payload;
    int pps_size = p_nal[1].i_payload;
    int sei_size = p_nal[2].i_payload;


    p_flv->sei = malloc( sei_size );
    if( !p_flv->sei )
        return -1;
    p_flv->sei_len = sei_size;

    memcpy( p_flv->sei, p_nal[2].p_payload, sei_size );


    uint8_t *sps = p_nal[0].p_payload + 4;

    flv_put_byte( c, FLV_TAG_TYPE_VIDEO );
    flv_put_be24( c, 0 );
    flv_put_be24( c, 0 );
    flv_put_byte( c, 0 );
    flv_put_be24( c, 0 );
    p_flv->start = c->d_cur;

    flv_put_byte( c, 7 | FLV_FRAME_KEY );
    flv_put_byte( c, 0 );
    flv_put_be24( c, 0 );

    flv_put_byte( c, 1 );
    flv_put_byte( c, sps[1] );
    flv_put_byte( c, sps[2] );
    flv_put_byte( c, sps[3] );
    flv_put_byte( c, 0xff );
    flv_put_byte( c, 0xe1 );

    flv_put_be16( c, sps_size - 4 );
    flv_append_data( c, sps, sps_size - 4 );


    flv_put_byte( c, 1 );
    flv_put_be16( c, pps_size - 4 );
    flv_append_data( c, p_nal[1].p_payload + 4, pps_size - 4 );


    unsigned length = c->d_cur - p_flv->start;
    flv_rewrite_amf_be24( c, length, p_flv->start - 10 );
    flv_put_be32( c, length + 11 );
    CHECK( flv_flush_data( c ) );

    return sei_size + sps_size + pps_size;
}
