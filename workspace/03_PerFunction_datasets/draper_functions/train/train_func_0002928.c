TraversePointSet2D(GF_Node *node, void *rs, Bool is_destroy)
{
	DrawableContext *ctx;
	M_PointSet2D *ps2D = (M_PointSet2D *)node;
	Drawable *stack = (Drawable *)gf_node_get_private(node);
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;

	if (is_destroy) {
		drawable_node_del(node);
		return;
	}

	if (!ps2D->coord) return;

	pointset2d_check_changes(node, stack, tr_state);

	switch (tr_state->traversing_mode) {
	case TRAVERSE_DRAW_2D:
		PointSet2D_Draw(node, tr_state);
		return;
#ifndef GPAC_DISABLE_3D
	case TRAVERSE_DRAW_3D:
	{
		DrawAspect2D asp;
		if (!stack->mesh) {
			stack->mesh = new_mesh();
			mesh_new_ps(stack->mesh, ps2D->coord, ps2D->color);
		}
		memset(&asp, 0, sizeof(DrawAspect2D));
		drawable_get_aspect_2d_mpeg4(node, &asp, tr_state);
		visual_3d_set_material_2d_argb(tr_state->visual, asp.fill_color);
		visual_3d_mesh_paint(tr_state, stack->mesh);
		return;
	}
#endif
	case TRAVERSE_GET_BOUNDS:
		gf_path_get_bounds(stack->path, &tr_state->bounds);
		return;
	case TRAVERSE_PICK:
		return;
	case TRAVERSE_SORT:
#ifndef GPAC_DISABLE_3D
		if (tr_state->visual->type_3d) return;
#endif
		ctx = drawable_init_context_mpeg4(stack, tr_state);
		if (!ctx) return;
		drawable_finalize_sort(ctx, tr_state, NULL);
		break;
	default:
		return;
	}
}
