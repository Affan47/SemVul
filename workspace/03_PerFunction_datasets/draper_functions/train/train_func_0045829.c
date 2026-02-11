DestroySwallow(struct XObj *xobj)
{

	if (xobj->win!=None)
		XKillClient(dpy, xobj->win);
	xobj->win = None;
}
