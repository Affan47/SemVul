ewmh_set_net_wm_state(Client *c) {
	Atom state[3];
	int i = 0;
	if (c->oldh)
		state[i++] = xa_net_wm_state_maximized_vert;
	if (c->oldw)
		state[i++] = xa_net_wm_state_maximized_horz;
	if (c->oldh && c->oldw)
		state[i++] = xa_net_wm_state_fullscreen;
	XChangeProperty(dpy, c->window, xa_net_wm_state,
			XA_ATOM, 32, PropModeReplace,
			(unsigned char *)&state, i);
}
