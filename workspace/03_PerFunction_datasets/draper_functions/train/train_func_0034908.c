GetIconWindow(FvwmWindow *fw)
{
	int w;
	int h;
	int bw;

	fw->icon_g.picture_w_g.width = 0;
	fw->icon_g.picture_w_g.height = 0;


	if (XGetGeometry(
		    dpy, fw->wmhints->icon_window, &JunkRoot, &JunkX, &JunkY,
		    (unsigned int*)&w, (unsigned int*)&h,(unsigned int*)&bw,
		    (unsigned int*)&JunkDepth) == 0)
	{
		fvwm_msg(
			ERR,"GetIconWindow",
			"Window '%s' has a bad icon window! Ignoring icon"
			" window.", fw->name.name);

		fw->wmhints->icon_window = None;
		fw->wmhints->flags &= ~IconWindowHint;
		return;
	}
	fw->icon_border_width = bw;
	fw->icon_g.picture_w_g.width = w + 2 * bw;
	fw->icon_g.picture_w_g.height = h + 2 * bw;


	FW_W_ICON_PIXMAP(fw) = fw->wmhints->icon_window;
	if (FShapesSupported)
	{
		if (fw->wmhints->flags & IconMaskHint)
		{
			SET_ICON_SHAPED(fw, 1);
			fw->icon_maskPixmap = fw->wmhints->icon_mask;
		}
	}


	XReparentWindow(dpy, FW_W_ICON_PIXMAP(fw), Scr.Root, 0,0);
	SET_ICON_OURS(fw, 0);

	return;
}
