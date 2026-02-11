visual_del(GF_VisualManager *visual)
{
	ra_del(&visual->to_redraw);

	if (visual->raster_surface) visual->compositor->rasterizer->surface_delete(visual->raster_surface);
	visual->raster_surface = NULL;
	if (visual->raster_brush) visual->compositor->rasterizer->stencil_delete(visual->raster_brush);
	visual->raster_brush = NULL;

	while (visual->context) {
		DrawableContext *ctx = visual->context;
		visual->context = ctx->next;
		DeleteDrawableContext(ctx);
	}
	while (visual->prev_nodes) {
		struct _drawable_store *cur = visual->prev_nodes;
		visual->prev_nodes = cur->next;
		gf_free(cur);
	}

#ifndef GPAC_DISABLE_VRML
	if (visual->back_stack) BindableStackDelete(visual->back_stack);
	if (visual->view_stack) BindableStackDelete(visual->view_stack);
#endif

#ifndef GPAC_DISABLE_3D
	visual_3d_reset_graphics(visual);

#ifndef GPAC_DISABLE_VRML
	if (visual->navigation_stack) BindableStackDelete(visual->navigation_stack);
	if (visual->fog_stack) BindableStackDelete(visual->fog_stack);
#endif

	gf_list_del(visual->alpha_nodes_to_draw);
#endif
	gf_free(visual);
}
