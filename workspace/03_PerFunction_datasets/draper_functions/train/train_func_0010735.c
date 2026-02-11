showhide(Client *c) {
	if(!c)
		return;
	if(ISVISIBLE(c)) {
		XMoveWindow(dpy, c->win, c->x, c->y);
		if((!c->mon->lt[c->mon->sellt]->arrange || c->isfloating) && !c->isfullscreen)
			resize(c, c->x, c->y, c->w, c->h, False);
		showhide(c->snext);
	}
	else {
		showhide(c->snext);
		XMoveWindow(dpy, c->win, WIDTH(c) * -2, c->y);
	}
}
