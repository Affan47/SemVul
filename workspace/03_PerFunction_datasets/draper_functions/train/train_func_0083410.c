handle_property_change(XPropertyEvent *e) {
	Client *c = find_client(e->window);

	if (c) {
		LOG_ENTER("handle_property_change(window=%lx, atom=%s)", e->window, debug_atom_name(e->atom));
		if (e->atom == XA_WM_NORMAL_HINTS) {
			get_wm_normal_hints(c);
			LOG_DEBUG("geometry=%dx%d+%d+%d\n", c->width, c->height, c->x, c->y);
		} else if (e->atom == xa_net_wm_window_type) {
			get_window_type(c);
			if (!c->is_dock
#ifdef VWM
					&& (is_fixed(c) || (c->vdesk == c->screen->vdesk))
#endif
					) {
				client_show(c);
			}
		}
		LOG_LEAVE();
	}
}
