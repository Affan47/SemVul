xkl_xmm_get_server_state(XklEngine * engine, XklState * state)
{
	unsigned char *propval = NULL;
	Atom actual_type;
	int actual_format;
	unsigned long bytes_remaining;
	unsigned long actual_items;
	int result;

	memset(state, 0, sizeof(*state));

	result =
	    XGetWindowProperty(xkl_engine_get_display(engine),
			       xkl_engine_priv(engine, root_window),
			       xkl_engine_backend(engine, XklXmm,
						  state_atom), 0L, 1L,
			       False, XA_INTEGER, &actual_type,
			       &actual_format, &actual_items,
			       &bytes_remaining, &propval);

	if (Success == result) {
		if (actual_format == 32 || actual_items == 1) {
			state->group = *(CARD32 *) propval;
		} else {
			xkl_debug(160,
				  "Could not get the xmodmap current group\n");
		}
		XFree(propval);
	} else {
		xkl_debug(160,
			  "Could not get the xmodmap current group: %d\n",
			  result);
	}
}
