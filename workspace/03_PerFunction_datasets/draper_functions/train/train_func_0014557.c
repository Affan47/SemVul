fz_list_clip_stroke_path(fz_device *dev, fz_path *path, fz_rect *rect, fz_stroke_state *stroke, fz_matrix ctm)
{
	fz_display_node *node;
	fz_context *ctx = dev->ctx;
	node = fz_new_display_node(ctx, FZ_CMD_CLIP_STROKE_PATH, ctm, NULL, NULL, 0);
	fz_try(ctx)
	{
		node->rect = fz_bound_path(dev->ctx, path, stroke, ctm);
		if (rect)
			node->rect = fz_intersect_rect(node->rect, *rect);
		node->item.path = fz_clone_path(dev->ctx, path);
		node->stroke = fz_keep_stroke_state(dev->ctx, stroke);
	}
	fz_catch(ctx)
	{
		fz_free_display_node(ctx, node);
		fz_rethrow(ctx);
	}
	fz_append_display_node(dev->user, node);
}
