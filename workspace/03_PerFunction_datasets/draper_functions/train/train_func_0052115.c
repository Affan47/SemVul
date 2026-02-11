x11_event()
{
	XEvent Event;
	while ( XPending(mainDisplay) ) {
		XNextEvent(mainDisplay, &Event);
		switch (Event.type) {
		case Expose:
#ifdef DEBUG
			printf("asmail: x11_event: Expose event caught: (%d %d) (%d x %d)\n",
			       ((XExposeEvent *) & Event)->x,
			       ((XExposeEvent *) & Event)->y,
			       ((XExposeEvent *) & Event)->width,
			       ((XExposeEvent *) & Event)->height);
#endif
			if (Event.xexpose.count == 0) {

				draw_window(((XExposeEvent *) & Event)->window);
			}
			break;
		case ButtonPress:
			ButtonHandler(&Event);
			break;
		case ClientMessage:
			if ((Event.xclient.message_type == wm_protocols)
			    && (Event.xclient.data.l[0] == wm_delete_window)) {
#ifdef DEBUG
				printf("asmail: caught wm_delete_window, closing\n");
#endif
				x_cleanup();
			}
			break;
		}
	}
}
