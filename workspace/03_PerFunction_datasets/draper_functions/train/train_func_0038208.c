popup_and_grab(Widget gw, XEvent *event,
			   String *params, Cardinal *no_params)
{
    MenuKnappWidget	w = (MenuKnappWidget)gw;
    Widget		menu = w->menu_knapp.menu;
    Screen		*screen = XtScreen(w);
    Arg			args[2];
    Position		x, y;
    int			tmp;

    if (!w->knapp.active || event->type != ButtonPress ||
	w->menu_knapp.menu_state != MenuStateDown)
	return;

    if (!menu && !(menu = w->menu_knapp.menu = find_menu(w))) {
	fprintf(stderr, "MenuKnapp: Couldn't find popup menu widget: %s\n",
		w->menu_knapp.menu_name ? w->menu_knapp.menu_name : "(null)");
	return;
    }

    if (!XtIsSubclass(menu, menuShellWidgetClass)) {
	fprintf(stderr, "MenuKnapp: Widget %s is not a "
		"subclass of menuShell.\n", XtName(menu));
	return;
    }

    XtAddGrab((Widget)w, True, True);
    if (XtGrabPointer((Widget)w, True,
		      ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
		      GrabModeAsync, GrabModeAsync, None,
		      None, event->xbutton.time) != GrabSuccess) {
	XtRemoveGrab((Widget)w);
	fputs("MenuKnapp: Failed to grab pointer.\n", stderr);
	return;
    }

    if (!XtIsRealized(menu))
	XtRealizeWidget(menu);

    SetActiveMenuShell(menu, True);

    XtTranslateCoords((Widget)w, 0, 0, &x, &y);
    y += w->core.height + w->core.border_width;
    if (x < 0)
	x = 0;
    else {
	tmp = WidthOfScreen(screen) - menu->core.width;
	if (tmp >= 0 && x > tmp)
	    x = tmp;
    }
    if (y < 0)
	y = 0;
    else {
	tmp = HeightOfScreen(screen) - menu->core.height;
	if (tmp >= 0 && y > tmp)
	    y = tmp;
    }

    w->menu_knapp.menu_state = MenuStateUp;
    w->menu_knapp.start_time = event->xbutton.time;
    XtSetArg(args[0], XtNx, x);
    XtSetArg(args[1], XtNy, y);
    XtSetValues(menu, args, 2);
    XtPopup(menu, XtGrabNone);
    XtAddGrab(menu, False, False);
    XClearWindow(XtDisplay(w), XtWindow(w));
    Redisplay((Widget)w, NULL, NULL);
}
