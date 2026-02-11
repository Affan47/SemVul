vim2m_release(struct file *file)
{
	struct vim2m_dev *dev = video_drvdata(file);
	struct vim2m_ctx *ctx = file2ctx(file);

	dprintk(dev, "Releasing instance %p\n", ctx);

	v4l2_fh_del(&ctx->fh);
	v4l2_fh_exit(&ctx->fh);
	v4l2_ctrl_handler_free(&ctx->hdl);
	mutex_lock(&dev->dev_mutex);
	v4l2_m2m_ctx_release(ctx->fh.m2m_ctx);
	mutex_unlock(&dev->dev_mutex);
	kfree(ctx);

	atomic_dec(&dev->num_inst);

	return 0;
}
