run(void) {
	XEvent ev;


	while(running && !XNextEvent(dpy, &ev))
		switch (ev.type) {
		default:
			break;
		case KeyPress:
			kpress(&ev.xkey);
			break;
		case Expose:
			if(ev.xexpose.count == 0)
				drawmenu();
			break;
		}
}
