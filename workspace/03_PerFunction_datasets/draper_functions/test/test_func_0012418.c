PImageLoadXpm(FIMAGE_CMD_ARGS)
{
	FxpmImage xpm_im;
	FxpmColor *xpm_color;
	XColor color;
	CARD32 *colors;
	CARD32 *data;
	char *visual_color;
	int i;
	int w;
	int h;
	int rc;
#ifdef HAVE_SIGACTION
	struct sigaction defaultHandler;
	struct sigaction originalHandler;
#else
	RETSIGTYPE (*originalHandler)(int);
#endif

	if (!XpmSupport)
	{
		return False;
	}
	memset(&xpm_im, 0, sizeof(FxpmImage));

#ifdef HAVE_SIGACTION
	sigemptyset(&defaultHandler.sa_mask);
	defaultHandler.sa_flags = 0;
	defaultHandler.sa_handler = SIG_DFL;
	sigaction(SIGCHLD, &defaultHandler, &originalHandler);
#else
	originalHandler = signal(SIGCHLD, SIG_DFL);
#endif


	rc = FxpmReadFileToXpmImage(path, &xpm_im, NULL);

#ifdef HAVE_SIGACTION
	sigaction(SIGCHLD, &originalHandler, NULL);
#else
	signal(SIGCHLD, originalHandler);
#endif

	if (rc != FxpmSuccess)
	{
		return False;
	}

	if (xpm_im.ncolors <= 0)
	{
		FxpmFreeXpmImage(&xpm_im);
		return False;
	}
	colors = (CARD32 *)safemalloc(xpm_im.ncolors * sizeof(CARD32));
	for (i=0; i < xpm_im.ncolors; i++)
	{
		xpm_color = &xpm_im.colorTable[i];
		if (xpm_color->c_color)
		{
			visual_color = xpm_color->c_color;
		}
		else if (xpm_color->g_color)
		{
			visual_color = xpm_color->g_color;
		}
		else if (xpm_color->g4_color)
		{
			visual_color = xpm_color->g4_color;
		}
		else
		{
			visual_color = xpm_color->m_color;
		}
		if (XParseColor(dpy, Pcmap, visual_color, &color))
		{
			colors[i] = 0xff000000 |
				((color.red  << 8) & 0xff0000) |
				((color.green    ) & 0xff00) |
				((color.blue >> 8) & 0xff);
		}
		else
		{
			colors[i] = 0;
		}
	}
	*width = w = xpm_im.width;
	*height = h = xpm_im.height;
	data = (CARD32 *)safemalloc(w * h * sizeof(CARD32));
	for (i=0; i < w * h; i++)
	{
		data[i] = colors[xpm_im.data[i]];
	}
	free(colors);
	*argb_data = data;

	return True;
}
