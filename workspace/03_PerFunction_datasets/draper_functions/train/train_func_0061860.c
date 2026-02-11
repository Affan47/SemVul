movemouse(const Arg *arg) {
	int x, y, ocx, ocy, nx, ny;
	Client *c;
	Monitor *m;
	XEvent ev;

	if(!(c = selmon->sel))
		return;
	restack(selmon);
	ocx = c->x;
	ocy = c->y;
	if(XGrabPointer(dpy, root, False, MOUSEMASK, GrabModeAsync, GrabModeAsync,
	None, cursor[CurMove], CurrentTime) != GrabSuccess)
		return;
	if(!getrootptr(&x, &y))
		return;
	do {
		XMaskEvent(dpy, MOUSEMASK|ExposureMask|SubstructureRedirectMask, &ev);
		switch (ev.type) {
		case ConfigureRequest:
		case Expose:
		case MapRequest:
			handler[ev.type](&ev);
			break;
		case MotionNotify:
			nx = ocx + (ev.xmotion.x - x);
			ny = ocy + (ev.xmotion.y - y);
			if(snap && nx >= selmon->wx && nx <= selmon->wx + selmon->ww
			&& ny >= selmon->wy && ny <= selmon->wy + selmon->wh) {
				if(abs(selmon->wx - nx) < snap)
					nx = selmon->wx;
				else if(abs((selmon->wx + selmon->ww) - (nx + WIDTH(c))) < snap)
					nx = selmon->wx + selmon->ww - WIDTH(c);
				if(abs(selmon->wy - ny) < snap)
					ny = selmon->wy;
				else if(abs((selmon->wy + selmon->wh) - (ny + HEIGHT(c))) < snap)
					ny = selmon->wy + selmon->wh - HEIGHT(c);
				if(!c->isfloating && selmon->lt[selmon->sellt]->arrange
				&& (abs(nx - c->x) > snap || abs(ny - c->y) > snap))
					togglefloating(NULL);
			}
			if(!selmon->lt[selmon->sellt]->arrange || c->isfloating)
				resize(c, nx, ny, c->w, c->h, True);
			break;
		}
	} while(ev.type != ButtonRelease);
	XUngrabPointer(dpy, CurrentTime);
	if((m = ptrtomon(c->x + c->w / 2, c->y + c->h / 2)) != selmon) {
		sendmon(c, m);
		selmon = m;
		focus(NULL);
	}
}
