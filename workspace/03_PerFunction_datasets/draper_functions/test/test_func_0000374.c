_k_graph_rebuild_port_with_color(state_t *s, gfx_color_t newbgcolor)
{
	gfxw_port_t *port = s->port;
	gfxw_port_t *newport;

	newport = sciw_new_window(s, port->zone, port->font_nr, port->color, newbgcolor,
					       s->titlebar_port->font_nr, s->ega_colors[15], s->ega_colors[8],
					       port->title_text, port->port_flags & ~WINDOW_FLAG_TRANSPARENT);

	if (s->dyn_views) {
		int found = 0;
		gfxw_container_t *parent = s->dyn_views->parent;

		while (parent && !(found |= (GFXW(parent) == GFXW(port))))
			parent = parent->parent;

		s->dyn_views = NULL;
	}

	port->parent->add(GFXWC(port->parent), GFXW(newport));
	port->widfree(GFXW(port));
}
