gfxw_remove_port(gfxw_visual_t *visual, gfxw_port_t *port)
{
	gfxw_port_t *parent;
	VERIFY_WIDGET(visual);
	VERIFY_WIDGET(port);

	if (!visual->contents) {
		GFXWARN("Attempt to remove port from empty visual\n");
		return NULL;
	}

	parent = (gfxw_port_t *) port->parent;
	if (port->port_flags & WINDOW_FLAG_AUTO_RESTORE)
		gfxw_restore_snapshot(visual, port->restore_snap);

	if (port->widfree(GFXW(port)))
		return parent;

	while (parent && !GFXW_IS_PORT(parent))
		parent = (gfxw_port_t *) parent->parent;

	return parent;
}
