GXDraw_LayoutLineCount(GWindow w) {
#ifndef _NO_LIBPANGO
    if ( ((GXWindow) w)->usepango )
return( _GXPDraw_LayoutLineCount(w));
#endif
return( -1 );
}
