sst_cdev_fragment_elapsed(struct intel_sst_drv *ctx, int str_id)
{
	struct stream_info *stream;

	dev_dbg(ctx->dev, "fragment elapsed from firmware for str_id %d\n",
			str_id);
	stream = &ctx->streams[str_id];
	if (stream->compr_cb)
		stream->compr_cb(stream->compr_cb_param);
}
