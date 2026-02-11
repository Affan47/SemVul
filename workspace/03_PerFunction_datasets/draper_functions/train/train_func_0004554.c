show_info(Client *c, unsigned int keycode) {
	XEvent ev;
	XKeyboardState keyboard;

	if (XGrabKeyboard(dpy, c->screen->root, False, GrabModeAsync, GrabModeAsync, CurrentTime) != GrabSuccess)
		return;


	XGetKeyboardControl(dpy, &keyboard);
	XChangeKeyboardControl(dpy, KBAutoRepeatMode, &(XKeyboardControl){.auto_repeat_mode = AutoRepeatModeOff});
#ifdef INFOBANNER
	create_info_window(c);
#else
	XGrabServer(dpy);
	draw_outline(c);
#endif
	do {
		XMaskEvent(dpy, KeyReleaseMask, &ev);
		if (ev.xkey.keycode != keycode)
			continue;
		if (XCheckIfEvent(dpy, &ev, predicate_keyrepeatpress, (XPointer)&ev)) {


			continue;
		}
		break;
	} while (1);
#ifdef INFOBANNER
	remove_info_window();
#else
	draw_outline(c);
	XUngrabServer(dpy);
#endif
	XChangeKeyboardControl(dpy, KBAutoRepeatMode, &(XKeyboardControl){.auto_repeat_mode = keyboard.global_auto_repeat});
	XUngrabKeyboard(dpy, CurrentTime);
}
