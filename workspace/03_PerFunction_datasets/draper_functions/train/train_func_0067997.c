xlib_initialize(GVJ_t *firstjob)
{
    Display *dpy;
    KeySym keysym;
    KeyCode *keycodes;
    const char *display_name = NULL;
    int i, scr;

    dpy = XOpenDisplay(display_name);
    if (dpy == NULL) {
	fprintf(stderr, "Failed to open XLIB display: %s\n",
		XDisplayName(NULL));
	return;
    }
    scr = DefaultScreen(dpy);

    firstjob->display = (void*)dpy;
    firstjob->screen = scr;

    keycodes = (KeyCode *)malloc(firstjob->numkeys * sizeof(KeyCode));
    if (keycodes == NULL) {
        fprintf(stderr, "Failed to malloc %d*KeyCode\n", firstjob->numkeys);
        return;
    }
    for (i = 0; i < firstjob->numkeys; i++) {
        keysym = XStringToKeysym(firstjob->keybindings[i].keystring);
        if (keysym == NoSymbol)
            fprintf(stderr, "ERROR: No keysym for \"%s\"\n",
		firstjob->keybindings[i].keystring);
        else
            keycodes[i] = XKeysymToKeycode(dpy, keysym);
    }
    firstjob->keycodes = (void*)keycodes;

    firstjob->device_dpi.x = DisplayWidth(dpy, scr) * 25.4 / DisplayWidthMM(dpy, scr);
    firstjob->device_dpi.y = DisplayHeight(dpy, scr) * 25.4 / DisplayHeightMM(dpy, scr);
    firstjob->device_sets_dpi = TRUE;
}
