GXDrawDrawPoly(GWindow gw, GPoint *pts, int16 cnt, Color col) {
    GXWindow gxw = (GXWindow) gw;
    GXDisplay *display = gxw->display;

    gxw->ggc->fg = col;
#ifndef _NO_LIBCAIRO
    if ( gxw->usecairo ) {
	_GXCDraw_DrawPoly( gxw,pts,cnt);
    } else
#endif
    {
	GXDrawSetline(display,gxw->ggc);
	XDrawLines(display->display,gxw->w,display->gcstate[gxw->ggc->bitmap_col].gc,(XPoint *) pts,cnt,CoordModeOrigin);
    }
}
