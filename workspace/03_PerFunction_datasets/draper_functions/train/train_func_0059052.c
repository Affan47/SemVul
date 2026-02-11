my_xft_render_layout(XftDraw *xftw,XftColor *fgcol,
	PangoLayout *layout,int x,int y) {
    PangoRectangle rect, r2;
    PangoLayoutIter *iter;

    iter = _pango_layout_get_iter(layout);
    do {
	PangoLayoutRun *run = _pango_layout_iter_get_run(iter);
	if ( run!=NULL ) {
	    _pango_layout_iter_get_run_extents(iter,&r2,&rect);
	    _pango_xft_render(xftw,fgcol,run->item->analysis.font,run->glyphs,
		    x+(rect.x+PANGO_SCALE/2)/PANGO_SCALE, y+(rect.y+PANGO_SCALE/2)/PANGO_SCALE);

	}
    } while ( _pango_layout_iter_next_run(iter));
    _pango_layout_iter_free(iter);
}
