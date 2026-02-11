gfxw_find_default_port(gfxw_visual_t *visual)
{
	int id = visual->port_refs_nr;

	while (id--) {
		gfxw_port_t *port = visual->port_refs[id];

		if (port)
			return port;
	}

	return NULL;
}
