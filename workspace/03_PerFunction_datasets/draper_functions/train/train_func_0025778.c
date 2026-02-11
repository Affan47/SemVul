span_strike_3d(GF_TextSpan *span, GF_TraverseState *tr_state, DrawAspect2D *asp, Bool vect_outline)
{
	span_alloc_extensions(span);
	if (!span->ext->outline) {
		GF_Path *path = gf_font_span_create_path(span);
		span->ext->outline = new_mesh();
#ifdef GPAC_HAS_GLU
		if (vect_outline) {
			GF_Path *outline = gf_path_get_outline(path, asp->pen_props);
			gf_mesh_tesselate_path(span->ext->outline, outline, asp->line_texture ? 2 : 1);
			gf_path_del(outline);
		} else {
			mesh_get_outline(span->ext->outline, path);
		}
#else
		vect_outline = 0;
		mesh_get_outline(span->ext->outline, path);
#endif
		gf_path_del(path);
	}
	if (vect_outline) {
		visual_3d_mesh_paint(tr_state, span->ext->outline);
	} else {
		visual_3d_mesh_strike(tr_state, span->ext->outline, asp->pen_props.width, asp->line_scale, asp->pen_props.dash);
	}
}
