FGetFImage(
	Display *dpy, Drawable d, Visual *visual,
	unsigned int depth, int x, int y, unsigned int width,
	unsigned int height, unsigned long plane_mask, int format)
{
	FImage *fim;

	FShmInit(dpy);

	fim = (FImage *)safemalloc(sizeof(FImage));
	fim->im = NULL;
	fim->shminfo = NULL;

	if (XShmSupport && FShmImagesSupported)
	{
		FShmSafeCreateImage(
			dpy, fim, visual, depth, format, width, height);
		if (fim->im)
		{
			FShmGetImage(
				dpy, d, fim->im, x, y, plane_mask);
		}
	}

	if (!fim->im)
	{
		fim->im = XGetImage(
			dpy, d, x, y, width, height, plane_mask, format);
	}

	return fim;
}
