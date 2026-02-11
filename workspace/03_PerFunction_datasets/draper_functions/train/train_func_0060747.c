fz_knockout_begin(fz_draw_device *dev)
{
	fz_context *ctx = dev->ctx;
	fz_bbox bbox;
	fz_pixmap *dest, *shape;
	fz_draw_state *state = &dev->stack[dev->top];
	int isolated = state->blendmode & FZ_BLEND_ISOLATED;

	if ((state->blendmode & FZ_BLEND_KNOCKOUT) == 0)
		return state;

	state = push_stack(dev);

	bbox = fz_pixmap_bbox(dev->ctx, state->dest);
	bbox = fz_intersect_bbox(bbox, state->scissor);
	dest = fz_new_pixmap_with_bbox(dev->ctx, state->dest->colorspace, bbox);

	if (isolated)
	{
		fz_clear_pixmap(ctx, dest);
	}
	else
	{

		int i = dev->top-1;
		fz_pixmap *prev = state->dest;
		while (i > 0)
		{
			prev = dev->stack[--i].dest;
			if (prev != state->dest)
				break;
		}
		if (prev)
			fz_copy_pixmap_rect(ctx, dest, prev, bbox);
		else
			fz_clear_pixmap(ctx, dest);
	}

	if (state->blendmode == 0 && isolated)
	{


		shape = state->shape;
	}
	else
	{
		shape = fz_new_pixmap_with_bbox(dev->ctx, NULL, bbox);
		fz_clear_pixmap(dev->ctx, shape);
	}
#ifdef DUMP_GROUP_BLENDS
	dump_spaces(dev->top-1, "Knockout begin\n");
#endif
	state[1].scissor = bbox;
	state[1].dest = dest;
	state[1].shape = shape;
	state[1].blendmode &= ~FZ_BLEND_MODEMASK;

	return &state[1];
}
