fli_init_stipples( void )
{
    if ( ! fli_gray_pattern[ 0 ] )
    {
        fli_gray_pattern[ 0 ] =
            XCreateBitmapFromData( flx->display, fl_root,
                                   ( char * ) gray40_bits, 8, 8 );
        fli_gray_pattern[ 1 ] =
            XCreateBitmapFromData( flx->display, fl_root,
                                   ( char * ) gray50_bits, 8, 8 );
        fli_gray_pattern[ 2 ] =
            XCreateBitmapFromData( flx->display, fl_root,
                                   ( char * ) gray60_bits, 8, 8 );
    }
}
