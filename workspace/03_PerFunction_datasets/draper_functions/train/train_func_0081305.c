configurenotify(XEvent *e) {
	Monitor *m;
	XConfigureEvent *ev = &e->xconfigure;

	if(ev->window == root) {
		sw = ev->width;
		sh = ev->height;
		if(updategeom()) {
			if(dc.drawable != 0)
				XFreePixmap(dpy, dc.drawable);
			dc.drawable = XCreatePixmap(dpy, root, sw, bh, DefaultDepth(dpy, screen));
			updatebars();
			for(m = mons; m; m = m->next)
				XMoveResizeWindow(dpy, m->barwin, m->wx, m->by, m->ww, bh);
			arrange(NULL);
		}
	}
}
