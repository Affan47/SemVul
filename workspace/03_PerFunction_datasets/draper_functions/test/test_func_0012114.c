emmaprp_job_abort(void *priv)
{
	struct emmaprp_ctx *ctx = priv;
	struct emmaprp_dev *pcdev = ctx->dev;

	ctx->aborting = 1;

	dprintk(pcdev, "Aborting task\n");

	v4l2_m2m_job_finish(pcdev->m2m_dev, ctx->m2m_ctx);
}
