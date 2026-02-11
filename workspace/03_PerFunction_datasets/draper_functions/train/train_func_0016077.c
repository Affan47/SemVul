_GPSDraw_TileImage(GWindow w, GImage *image, GRect *dest, int32 x, int32 y) {
    GPSWindow ps = (GPSWindow) w;
    struct _GImage *base = image->list_len==0?image->u.image:image->u.images[0];
    int xstart, ystart, xend, yend;
    int factor = ps->display->scale_screen_by;
    int width = factor*base->width, height = factor*base->height;
    int i,j;

    xstart = (dest->x-x)/width; ystart = (dest->y-y)/height;
    xend = (dest->x+dest->width-x)/width; yend = (dest->y+dest->height-y)/height;
    if ( !PSTileImage(ps,base,
	    x+xstart*width,y+ystart*height,
	    xend-xstart+1,yend-ystart+1)) {
	GRect src; src.x = src.y = 0; src.width = base->width; src.height = height;
	for ( j=ystart; j<=yend; ++j ) for ( i=xstart; i<=xend; ++i ) {
	    GRect dest;
	    dest.x = x+i*width; dest.y = y+j*height;
	    dest.width = width; dest.height = height;
	    PSDrawImage(ps,image, &dest, &src);
	}
    }
}
