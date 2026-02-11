DrawArrowW(struct XObj *xobj, int x, int y, int Press)
{
	XSegment segm[4];

	segm[0].x1 = 2+x;
	segm[0].y1 = 5+y;
	segm[0].x2 = 12+x;
	segm[0].y2 = 0+y;
	segm[1].x1 = 4+x;
	segm[1].y1 = 5+y;
	segm[1].x2 = 10+x;
	segm[1].y2 = 2+y;
	if (Press == 1)
		XSetForeground(dpy, xobj->gc, xobj->TabColor[shad]);
	else
		XSetForeground(dpy, xobj->gc, xobj->TabColor[hili]);
	XDrawSegments(dpy, xobj->win, xobj->gc, segm, 2);

	segm[0].x1 = 0+x;
	segm[0].y1 = 6+y;
	segm[0].x2 = 12+x;
	segm[0].y2 = 12+y;
	segm[1].x1 = 2+x;
	segm[1].y1 = 6+y;
	segm[1].x2 = 11+x;
	segm[1].y2 = 10+y;

	segm[2].x1 = 12+x;
	segm[2].y1 = 1+y;
	segm[2].x2 = 12+x;
	segm[2].y2 = 12+y;
	segm[3].x1 = 11+x;
	segm[3].y1 = 2+y;
	segm[3].x2 = 11+x;
	segm[3].y2 = 11+y;
	if (Press == 1)
		XSetForeground(dpy, xobj->gc, xobj->TabColor[hili]);
	else
		XSetForeground(dpy, xobj->gc, xobj->TabColor[shad]);
	XDrawSegments(dpy, xobj->win, xobj->gc, segm, 4);
}
