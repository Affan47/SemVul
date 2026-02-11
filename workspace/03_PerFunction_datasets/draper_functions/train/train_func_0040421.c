jpu_open(struct file *file)
{
	struct jpu *jpu = video_drvdata(file);
	struct video_device *vfd = video_devdata(file);
	struct jpu_ctx *ctx;
	int ret;

	ctx = kzalloc(sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	v4l2_fh_init(&ctx->fh, vfd);
	ctx->fh.ctrl_handler = &ctx->ctrl_handler;
	file->private_data = &ctx->fh;
	v4l2_fh_add(&ctx->fh);

	ctx->jpu = jpu;
	ctx->encoder = vfd == &jpu->vfd_encoder;

	__jpu_try_fmt(ctx, &ctx->out_q.fmtinfo, &ctx->out_q.format,
		      V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE);
	__jpu_try_fmt(ctx, &ctx->cap_q.fmtinfo, &ctx->cap_q.format,
		      V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE);

	ctx->fh.m2m_ctx = v4l2_m2m_ctx_init(jpu->m2m_dev, ctx, jpu_queue_init);
	if (IS_ERR(ctx->fh.m2m_ctx)) {
		ret = PTR_ERR(ctx->fh.m2m_ctx);
		goto v4l_prepare_rollback;
	}

	ret = jpu_controls_create(ctx);
	if (ret < 0)
		goto v4l_prepare_rollback;

	if (mutex_lock_interruptible(&jpu->mutex)) {
		ret = -ERESTARTSYS;
		goto v4l_prepare_rollback;
	}

	if (jpu->ref_count == 0) {
		ret = clk_prepare_enable(jpu->clk);
		if (ret < 0)
			goto device_prepare_rollback;

		ret = jpu_reset(jpu);
		if (ret)
			goto device_prepare_rollback;
	}

	jpu->ref_count++;

	mutex_unlock(&jpu->mutex);
	return 0;

device_prepare_rollback:
	mutex_unlock(&jpu->mutex);
v4l_prepare_rollback:
	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	kfree(ctx);
	return ret;
}
