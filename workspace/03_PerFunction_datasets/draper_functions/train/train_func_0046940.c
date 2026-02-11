make_menu_window(MenuRoot *mr, Bool is_tear_off)
{
	unsigned long valuemask;
	XSetWindowAttributes attributes;
	int w;
	int h;
	unsigned int evmask;

	w = MR_WIDTH(mr);
	if (w == 0)
	{
		w = 1;
	}
	h = MR_HEIGHT(mr);
	if (h == 0)
	{
		h = 1;
	}

	attributes.background_pixel = (MST_HAS_MENU_CSET(mr)) ?
		Colorset[MST_CSET_MENU(mr)].bg : MST_MENU_COLORS(mr).back;
	if (MR_WINDOW(mr) != None)
	{

		XResizeWindow(dpy, MR_WINDOW(mr), w, h);

		valuemask = CWBackPixel | CWCursor;
		XChangeWindowAttributes(
			dpy, MR_WINDOW(mr), valuemask, &attributes);
	}
	else
	{

		valuemask = CWBackPixel | CWEventMask | CWCursor | CWColormap
			| CWBorderPixel | CWSaveUnder;
		attributes.border_pixel = 0;
		attributes.colormap = Pcmap;
		evmask = XEVMASK_MENUW;
		attributes.event_mask = 0;
		attributes.cursor = Scr.FvwmCursors[CRS_MENU];
		attributes.save_under = True;


		if (is_tear_off)
		{
			MR_CREATE_DPY(mr) = XOpenDisplay(display_name);
			if (MR_CREATE_DPY(mr) == NULL)
			{

				MR_CREATE_DPY(mr) = dpy;
			}
		}
		else
		{
			MR_CREATE_DPY(mr) = dpy;
		}
		MR_WINDOW(mr) = XCreateWindow(
			MR_CREATE_DPY(mr), Scr.Root, 0, 0, w, h,
			0, Pdepth, InputOutput, Pvisual, valuemask,
			&attributes);
		if (MR_CREATE_DPY(mr) != dpy)
		{


			XSync(MR_CREATE_DPY(mr), 1);
		}
		if (MR_WINDOW(mr) != None)
		{


			XSelectInput(dpy, MR_WINDOW(mr), evmask);
		}
		XSaveContext(dpy, MR_WINDOW(mr), MenuContext,(caddr_t)mr);
	}

	return;
}
