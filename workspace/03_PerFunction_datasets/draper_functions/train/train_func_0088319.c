tga_get_pixel( FILE * tga, ubyte bytes_per_pix,
                            ubyte * colormap, ubyte cmap_bytes_entry ) {


    uint32 tmp_col;
    uint32 tmp_int32;
    ubyte tmp_byte;

    uint32 j;

    tmp_int32 = 0;
    for( j = 0; j < bytes_per_pix; j++ ) {
        if( fread( &tmp_byte, 1, 1, tga ) < 1 ) {
            tmp_int32 = 0;
        } else {
            tmp_int32 += tmp_byte << (j * 8);
        }
    }


    switch( bytes_per_pix ) {

    case 2:
        tmp_int32 = ttohs( (uint16)tmp_int32 );
        break;

    case 3:
    case 4:
        tmp_int32 = ttohl( tmp_int32 );
        break;

    }

    if( colormap != NULL ) {

        tmp_col = 0;
        for( j = 0; j < cmap_bytes_entry; j++ ) {
            tmp_col += colormap[cmap_bytes_entry * tmp_int32 + j] << (8 * j);
        }
    } else {
        tmp_col = tmp_int32;
    }

    return( tmp_col );

}
