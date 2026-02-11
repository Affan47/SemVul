fz_draw_pop_clip(fz_device *devp)
{
	fz_draw_device *dev = devp->user;
	fz_context *ctx = dev->ctx;
	fz_draw_state *state;

	if (dev->top == 0)
	{
		fz_warn(ctx, "Unexpected pop clip");
		return;
	}
	state = &dev->stack[--dev->top];


	if (state[1].mask)
	{
#ifdef DUMP_GROUP_BLENDS
		dump_spaces(dev->top, "");
		fz_dump_blend(dev->ctx, state[1].dest, "Clipping ");
		if (state[1].shape)
			fz_dump_blend(dev->ctx, state[1].shape, "/");
		fz_dump_blend(dev->ctx, state[0].dest, " onto ");
		if (state[0].shape)
			fz_dump_blend(dev->ctx, state[0].shape, "/");
		fz_dump_blend(dev->ctx, state[1].mask, " with ");
#endif
		fz_paint_pixmap_with_mask(state[0].dest, state[1].dest, state[1].mask);
		if (state[0].shape != state[1].shape)
		{
			fz_paint_pixmap_with_mask(state[0].shape, state[1].shape, state[1].mask);
			fz_drop_pixmap(dev->ctx, state[1].shape);
		}
		fz_drop_pixmap(dev->ctx, state[1].mask);
		fz_drop_pixmap(dev->ctx, state[1].dest);
#ifdef DUMP_GROUP_BLENDS
		fz_dump_blend(dev->ctx, state[0].dest, " to get ");
		if (state[0].shape)
			fz_dump_blend(dev->ctx, state[0].shape, "/");
		printf("\n");
#endif
	}
	else
	{
#ifdef DUMP_GROUP_BLENDS
		dump_spaces(dev->top, "Clip end\n");
#endif
	}
}
