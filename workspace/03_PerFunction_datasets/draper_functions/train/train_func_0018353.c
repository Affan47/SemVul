MapMain(PLStream *pls)
{
    XwDev *dev = (XwDev *) pls->dev;
    XwDisplay *xwd = (XwDisplay *) dev->xwd;
    XEvent event;

    dbug_enter("MapMain");


    dev->event_mask =
	ButtonPressMask      |
	KeyPressMask         |
	ExposureMask         |
	ButtonMotionMask     |
	StructureNotifyMask;

    XSelectInput(xwd->display, dev->window, dev->event_mask);


    XMapRaised(xwd->display, dev->window);


    for (;;) {
	XWindowEvent(xwd->display, dev->window, dev->event_mask, &event);
	if (event.type == Expose) {
	    while (XCheckWindowEvent(xwd->display, dev->window,
				     ExposureMask, &event));
	    break;
	}
    }
}
