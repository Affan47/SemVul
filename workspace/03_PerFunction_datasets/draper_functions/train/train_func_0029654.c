use_window(int win_id)
{
    XWindowAttributes xwa;

    external_window = 1;

    grwin = (Window) win_id;
    XSelectInput(dpy, grwin, gemask);

    if (!XGetWindowAttributes(dpy, grwin, &xwa))
	G_fatal_error("Graph_Set: cannot get window attributes\n");

    use_screen = xwa.screen;
    scrn = XScreenNumberOfScreen(xwa.screen);

    use_visual = xwa.visual;

    use_bit_depth = xwa.depth;
}
