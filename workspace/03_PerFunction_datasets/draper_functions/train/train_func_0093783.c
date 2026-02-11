md5_mem( void* ptr, int len ){

    static const md5_byte_t pad[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            };
    md5_byte_t data[8];
    int i, ret;
	  md5_state_t state;
    md5_init( &state );
    md5_append( &state, ptr, len );


    for (i = 0; i < 8; ++i)
         data[i] = (md5_byte_t)(state.count[i >> 2] >> ((i & 3) << 3));

    md5_append(&state, pad, ((55 - (state.count[0] >> 3)) & 63) + 1);

    md5_append(&state, data, 8);


    memcpy( &ret, state.abcd, sizeof( int ) );

    return ret;


}
