panel_multiscreen_init_randr (GdkDisplay *display)
{
#ifdef HAVE_RANDR
	Display *xdisplay;
	int      event_base, error_base;
#endif

	have_randr = FALSE;
	have_randr_1_3 = FALSE;

#ifdef HAVE_RANDR
	xdisplay = GDK_DISPLAY_XDISPLAY (display);


	if (XRRQueryExtension (xdisplay, &event_base, &error_base)) {
		int major, minor;

		XRRQueryVersion (xdisplay, &major, &minor);
		if ((major == 1 && minor >= 2) || major > 1)
			have_randr = TRUE;

		if ((major == 1 && minor >= 3) || major > 1)
			have_randr_1_3 = TRUE;
	}
#endif
}
