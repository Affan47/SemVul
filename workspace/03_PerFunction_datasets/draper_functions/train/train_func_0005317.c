TraverseIndexedCurve2D(GF_Node *node, void *rs, Bool is_destroy)
{
	DrawableContext *ctx;
	IndexedCurve2D ic2d;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	Drawable *stack = (Drawable *)gf_node_get_private(node);

	if (is_destroy) {
		drawable_node_del(node);
		return;
	}

	if (gf_node_dirty_get(node)) {
		if (!IndexedCurve2D_GetNode(node, &ic2d)) return;
		curve2d_check_changes((GF_Node*) &ic2d, stack, tr_state, &ic2d.index);
	}

	switch (tr_state->traversing_mode) {
#ifndef GPAC_DISABLE_3D
	case TRAVERSE_DRAW_3D:
		if (!stack->mesh) {
			stack->mesh = new_mesh();
			mesh_from_path(stack->mesh, stack->path);
		}
		visual_3d_draw_2d(stack, tr_state);
		return;
#endif
	case TRAVERSE_PICK:
		vrml_drawable_pick(stack, tr_state);
		return;
	case TRAVERSE_GET_BOUNDS:
		gf_path_get_bounds(stack->path, &tr_state->bounds);
		return;
	case TRAVERSE_SORT:
#ifndef GPAC_DISABLE_3D
		if (tr_state->visual->type_3d) return;
#endif
		ctx = drawable_init_context_mpeg4(stack, tr_state);
		if (!ctx) return;
		drawable_finalize_sort(ctx, tr_state, NULL);
		return;
	}
}
