PSBuildImage24String(GPSWindow ps,struct _GImage *base,GRect *src) {
    int i;
    register long val, trans = base->trans;
    register uint32 *pt, *end;
    int do_color = ps->display->do_color;

    InitFilter(ps);
    for ( i=src->y; i<src->y+src->height; ++i ) {
	pt = (uint32 *) (base->data + i*base->bytes_per_line) + src->x;
	end = pt + src->width;
	while ( pt<end ) {
	    if ((val = *pt++)==trans ) val = COLOR_CREATE(0xff,0xff,0xff);
	    if ( do_color ) {
		Filter(ps,COLOR_RED(val));
		Filter(ps,COLOR_GREEN(val));
		Filter(ps,COLOR_BLUE(val));
	    } else {
		Filter(ps,COLOR2GREY(val));
	    }
	}
    }
    FlushFilter(ps);
}
