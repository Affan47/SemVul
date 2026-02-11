DrawRelief(struct XObj *xobj)
{
	XSegment segm[2];
	int i;

	if (xobj->value!=0)
	{
		for (i=1;i<2;i++)
		{
			segm[0].x1=xobj->x-i;
			segm[0].y1=xobj->y-i;
			segm[0].x2=xobj->x+xobj->width+i-2;
			segm[0].y2=xobj->y-i;
			segm[1].x1=xobj->x-i;
			segm[1].y1=xobj->y-i;
			segm[1].x2=xobj->x-i;
			segm[1].y2=xobj->y+xobj->height+i-2;
			if (xobj->value==-1)
				XSetForeground(
					dpy,xobj->gc,xobj->TabColor[shad]);
			else
				XSetForeground(
					dpy,xobj->gc,xobj->TabColor[hili]);
			XDrawSegments(dpy,x11base->win,xobj->gc,segm,2);

			segm[0].x1=xobj->x-i;
			segm[0].y1=xobj->y+xobj->height+i-1;
			segm[0].x2=xobj->x+xobj->width+i-1;
			segm[0].y2=xobj->y+xobj->height+i-1;
			segm[1].x1=xobj->x+xobj->width+i-1;
			segm[1].y1=xobj->y-i;
			segm[1].x2=xobj->x+xobj->width+i-1;
			segm[1].y2=xobj->y+xobj->height+i-1;
			if (xobj->value==-1)
				XSetForeground(
					dpy,xobj->gc,xobj->TabColor[hili]);
			else
				XSetForeground(
					dpy,xobj->gc,xobj->TabColor[shad]);
			XDrawSegments(dpy,x11base->win,xobj->gc,segm,2);
		}
	}

}
