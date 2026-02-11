visual_2d_get_drawable_context(GF_VisualManager *visual)
{
#ifdef SKIP_CONTEXT
	return NULL;
#endif

	if (!visual->context) {
		visual->context = NewDrawableContext();
		visual->cur_context = visual->context;
		drawctx_reset(visual->context);
		visual->num_nodes_current_frame ++;
		return visual->context;
	}


	if (!visual->cur_context->drawable) {

		if (visual->cur_context->next) visual->cur_context->next->drawable = NULL;
		drawctx_reset(visual->cur_context);
		return visual->cur_context;
	}

	if (visual->cur_context->next) {
		visual->cur_context = visual->cur_context->next;


		if (visual->cur_context->next) visual->cur_context->next->drawable = NULL;
		drawctx_reset(visual->cur_context);
		visual->num_nodes_current_frame ++;
		return visual->cur_context;
	}

	visual->cur_context->next = NewDrawableContext();
	visual->cur_context = visual->cur_context->next;
	drawctx_reset(visual->cur_context);
	visual->num_nodes_current_frame ++;

	if (1) {
		u32 i;
		DrawableContext *last = visual->cur_context;
		for (i=0; i<50; i++) {
			last->next = gf_malloc(sizeof(DrawableContext));
			last = last->next;
			last->drawable = NULL;
			last->col_mat = NULL;
		}
		last->next = NULL;
	}
	return visual->cur_context;
}
