DrawRadioButton(struct XObj *xobj, XEvent *evp)
{
	int i,j;

	j=xobj->height/2+3;
	i=16;

	XSetForeground(dpy,xobj->gc,xobj->TabColor[shad]);
	XDrawArc(dpy,xobj->win,xobj->gc,1,j-11,11,11,45*64,180*64);
	XSetForeground(dpy,xobj->gc,xobj->TabColor[hili]);
	XDrawArc(dpy,xobj->win,xobj->gc,1,j-11,11,11,225*64,180*64);
	XSetForeground(dpy,xobj->gc,xobj->TabColor[shad]);
	XDrawArc(dpy,xobj->win,xobj->gc,2,j-10,9,9,0*64,360*64);
	XSetForeground(dpy,xobj->gc,xobj->TabColor[fore]);
	if (xobj->value)
		XFillArc(dpy,xobj->win,xobj->gc,2,j-10,9,9,0*64,360*64);


	MyDrawString(dpy,xobj,xobj->win,i,j,xobj->title,fore,hili,
		     back,!xobj->flags[1], NULL, evp);
}
