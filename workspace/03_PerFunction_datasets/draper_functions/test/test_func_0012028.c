gfxr_interpreter_get_view(gfx_resstate_t *state, int nr, void *internal, int palette)
{
	resource_mgr_t *resmgr = (resource_mgr_t *) state->misc_payload;
	resource_t *res = scir_find_resource(resmgr, sci_view, nr, 0);
	int resid = GFXR_RES_ID(GFX_RESOURCE_TYPE_VIEW, nr);
	gfxr_view_t *result;

	if (!res || !res->data)
		return NULL;

	if (state->version < SCI_VERSION_01) palette=-1;

	switch (state->version)
	{
	case SCI_VERSION_0:
	case SCI_VERSION_01:
		result=gfxr_draw_view0(resid, res->data, res->size, palette);
		break;
	case SCI_VERSION_01_VGA:
	case SCI_VERSION_01_VGA_ODD:
	case SCI_VERSION_1_EARLY:
	case SCI_VERSION_1_LATE:
		result=gfxr_draw_view1(resid, res->data, res->size, state->static_palette, state->static_palette_entries);
		break;
	case SCI_VERSION_1_1:
	case SCI_VERSION_32:
		result=gfxr_draw_view11(resid, res->data, res->size);
		break;
	}

	if (state->version >= SCI_VERSION_01_VGA)
	{
		    if (!result->colors)
		    {
			result->colors = (gfx_pixmap_color_t*)sci_malloc(sizeof(gfx_pixmap_color_t) * state->static_palette_entries);
			memset(result->colors, 0, sizeof(gfx_pixmap_color_t) * state->static_palette_entries);
			result->colors_nr = state->static_palette_entries;
		    }
		    gfxr_palettize_view(result, state->static_palette, state->static_palette_entries);
	}
	return result;
}
