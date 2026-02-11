drag(Client *c) {
	XEvent ev;
	int x1, y1;
	int old_cx = c->x;
	int old_cy = c->y;

	if (!grab_pointer(c->screen->root, MouseMask, move_curs)) return;
	client_raise(c);
	get_mouse_position(&x1, &y1, c->screen->root);
#ifdef INFOBANNER_MOVERESIZE
	create_info_window(c);
#endif
	if (no_solid_drag) {
		XGrabServer(dpy);
		draw_outline(c);
	}
	for (;;) {
		XMaskEvent(dpy, MouseMask, &ev);
		switch (ev.type) {
			case MotionNotify:
				if (ev.xmotion.root != c->screen->root)
					break;
				if (no_solid_drag) {
					draw_outline(c);
					XUngrabServer(dpy);
				}
				c->x = old_cx + (ev.xmotion.x - x1);
				c->y = old_cy + (ev.xmotion.y - y1);
				if (opt_snap && !(ev.xmotion.state & altmask))
					snap_client(c);

#ifdef INFOBANNER_MOVERESIZE
				update_info_window(c);
#endif
				if (no_solid_drag) {
					XSync(dpy, False);
					XGrabServer(dpy);
					draw_outline(c);
				} else {
					XMoveWindow(dpy, c->parent,
							c->x - c->border,
							c->y - c->border);
					send_config(c);
				}
				break;
			case ButtonRelease:
				if (no_solid_drag) {
					draw_outline(c);
					XUngrabServer(dpy);
				}
#ifdef INFOBANNER_MOVERESIZE
				remove_info_window();
#endif
				XUngrabPointer(dpy, CurrentTime);
				if (no_solid_drag) {
					moveresize(c);
				}
				return;
			default: break;
		}
	}
}
