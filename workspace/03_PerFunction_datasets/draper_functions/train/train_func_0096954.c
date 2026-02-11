skl_cldma_fill_buffer(struct sst_dsp *ctx, unsigned int size,
		const void *curr_pos, bool intr_enable, bool trigger)
{
	dev_dbg(ctx->dev, "Size: %x, intr_enable: %d\n", size, intr_enable);
	dev_dbg(ctx->dev, "buf_pos_index:%d, trigger:%d\n",
			ctx->cl_dev.dma_buffer_offset, trigger);
	dev_dbg(ctx->dev, "spib position: %d\n", ctx->cl_dev.curr_spib_pos);

	memcpy(ctx->cl_dev.dmab_data.area + ctx->cl_dev.dma_buffer_offset,
			curr_pos, size);

	if (ctx->cl_dev.curr_spib_pos == ctx->cl_dev.bufsize)
		ctx->cl_dev.dma_buffer_offset = 0;
	else
		ctx->cl_dev.dma_buffer_offset = ctx->cl_dev.curr_spib_pos;

	ctx->cl_dev.wait_condition = false;

	if (intr_enable)
		skl_cldma_int_enable(ctx);

	ctx->cl_dev.ops.cl_setup_spb(ctx, ctx->cl_dev.curr_spib_pos, trigger);
	if (trigger)
		ctx->cl_dev.ops.cl_trigger(ctx, true);
}
