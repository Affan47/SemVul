show_knife(ModeInfo *mi, unsigned long color, Trace *s)
{
	jugglestruct *sp = &juggles[MI_SCREEN(mi)];
	unsigned int i;
	const double sa = sin(s->angle);
	const double ca = cos(s->angle);


  	static const XPoint knife[] = {
	  {-24, 0},
	  { -5,-3},
	  { 16,-3},
	  { 12, 0},
	  { -5, 0},
	  { -5, 3},
	};
	XPoint a[XtNumber(knife)], p[5];


	if(s->y*sp->scale >  MI_HEIGHT(mi) * 2) return;


	for(i = 0; i < XtNumber(knife); i++) {
	  a[i].x = (short)(MI_WIDTH(mi)/2 +
					   (s->x + knife[i].x*PERSPEC*sa)*sp->scale -
					   knife[i].y*sqrt(sp->scale)*ca*PERSPEC);
	  a[i].y = (short)(MI_HEIGHT(mi) - (s->y - knife[i].x*ca)*sp->scale +
					   knife[i].y*sa*sqrt(sp->scale));
	}


	XSetForeground(MI_DISPLAY(mi), MI_GC(mi), color);
	XSetLineAttributes(MI_DISPLAY(mi), MI_GC(mi), (short)(4*sqrt(sp->scale)),
					   LineSolid, CapRound, JoinRound);
	XDrawLine(MI_DISPLAY(mi), MI_WINDOW(mi), MI_GC(mi),
			  a[0].x, a[0].y, a[4].x, a[4].y);


	if(color != MI_BLACK_PIXEL(mi)) {
	  XSetForeground(MI_DISPLAY(mi), MI_GC(mi), MI_WHITE_PIXEL(mi));
	}
	i = 0;
	p[i++] = a[1]; p[i++] = a[2]; p[i++] = a[3]; p[i++] = a[5];
	XFillPolygon(MI_DISPLAY(mi), MI_WINDOW(mi), MI_GC(mi),
				 p, i, Convex, CoordModeOrigin);
}
