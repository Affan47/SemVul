set_source_for_ref_type (cairo_t  *context,
                         GitgRef  *ref,
                         gboolean  use_state)
{
	if (use_state)
	{
		GitgRefState state = gitg_ref_get_state (ref);

		if (state == GITG_REF_STATE_SELECTED)
		{
			cairo_set_source_rgb (context, 1, 1, 1);
			return;
		}
		else if (state == GITG_REF_STATE_PRELIGHT)
		{
			gdouble r, g, b;
			get_ref_color (ref, &r, &g, &b);

			cairo_set_source_rgba (context, r, g, b, 0.3);
			return;
		}
	}

	gdouble r, g, b;
	get_ref_color (ref, &r, &g, &b);

	cairo_set_source_rgb (context, r, g, b);
}
