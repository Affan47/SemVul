_gfxwop_port_free(gfxw_widget_t *widget)
{
	gfxw_port_t *port = (gfxw_port_t *) widget;

	if (port->visual) {
		gfxw_visual_t *visual = port->visual;
		int ID = port->ID;

		if (ID < 0 || ID >= visual->port_refs_nr) {
			GFXWARN("Attempt to free port #%d; allowed: [0..%d]!\n", ID, visual->port_refs_nr);
			return GFX_ERROR;
		}

		if (visual->port_refs[ID] != port) {
			GFXWARN("While freeing port %d: Port is at %p, but port list indicates %p!\n",
				ID, port, visual->port_refs[ID]);
		} else visual->port_refs[ID] = NULL;

	}

	if (port->decorations)
		port->decorations->widfree(GFXW(port->decorations));

	return _gfxwop_container_free(widget);
}
