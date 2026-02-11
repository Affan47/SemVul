fli_check_key_focus( const char * s,
                     Window       win )
{
    int r;
    Window w;

    if ( fli_cntl.debug > 1 )
    {
        XGetInputFocus( flx->display, &w, &r );
        M_info( "fli_check_key_focus", "%s:%s FWin = %lu ReqW = %lu",
                s ? s : "", w == win ? "OK" : "Wrong", w, win );
    }
}
