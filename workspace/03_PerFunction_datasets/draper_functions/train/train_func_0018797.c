_visual_find_free_ID(gfxw_visual_t *visual)
{
	int id = 0;
	int newports = 16;

	while (visual->port_refs[id] && id < visual->port_refs_nr)
		id++;

	if (id == visual->port_refs_nr) {
		visual->port_refs = (struct _gfxw_port**)sci_realloc(visual->port_refs, visual->port_refs_nr += newports);
		memset(visual->port_refs + id, 0, newports * sizeof(gfxw_port_t *));
	}

	return id;
}
