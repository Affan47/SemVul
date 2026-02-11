btcx_align(struct v4l2_rect *win, struct v4l2_clip *clips, unsigned int n, int mask)
{
	s32 nx,nw,dx;
	unsigned int i;


	nx = (win->left + mask) & ~mask;
	nw = (win->width) & ~mask;
	if (nx + nw > win->left + win->width)
		nw -= mask+1;
	dx = nx - win->left;
	win->left  = nx;
	win->width = nw;
	if (btcx_debug)
		printk(KERN_DEBUG "btcx: window align %dx%d+%d+%d [dx=%d]\n",
		       win->width, win->height, win->left, win->top, dx);


	for (i = 0; i < n; i++) {
		nx = (clips[i].c.left-dx) & ~mask;
		nw = (clips[i].c.width) & ~mask;
		if (nx + nw < clips[i].c.left-dx + clips[i].c.width)
			nw += mask+1;
		clips[i].c.left  = nx;
		clips[i].c.width = nw;
		if (btcx_debug)
			printk(KERN_DEBUG "btcx:   clip align %dx%d+%d+%d\n",
			       clips[i].c.width, clips[i].c.height,
			       clips[i].c.left, clips[i].c.top);
	}
	return 0;
}
