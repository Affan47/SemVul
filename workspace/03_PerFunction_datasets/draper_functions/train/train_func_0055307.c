Restart()

{
    png_destroy_read_struct( &hPNG, &psPNGInfo, NULL );

    hPNG = png_create_read_struct( PNG_LIBPNG_VER_STRING, this, NULL, NULL );

    png_set_error_fn( hPNG, &sSetJmpContext, png_gdal_error, png_gdal_warning );
    if( setjmp( sSetJmpContext ) != 0 )
        return;

    psPNGInfo = png_create_info_struct( hPNG );

    VSIFSeekL( fpImage, 0, SEEK_SET );
    png_set_read_fn( hPNG, fpImage, png_vsi_read_data );
    png_read_info( hPNG, psPNGInfo );

    if( nBitDepth < 8 )
        png_set_packing( hPNG );

    nLastLineRead = -1;
}
