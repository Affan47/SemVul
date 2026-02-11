bdisp_ctx_stop_req(struct bdisp_ctx *ctx)
{
	struct bdisp_ctx *curr_ctx;
	struct bdisp_dev *bdisp = ctx->bdisp_dev;
	int ret;

	dev_dbg(ctx->bdisp_dev->dev, "%s\n", __func__);

	cancel_delayed_work(&bdisp->timeout_work);

	curr_ctx = v4l2_m2m_get_curr_priv(bdisp->m2m.m2m_dev);
	if (!test_bit(ST_M2M_RUNNING, &bdisp->state) || (curr_ctx != ctx))
		return 0;

	bdisp_ctx_state_lock_set(BDISP_CTX_STOP_REQ, ctx);

	ret = wait_event_timeout(bdisp->irq_queue,
			!bdisp_ctx_state_is_set(BDISP_CTX_STOP_REQ, ctx),
			BDISP_WORK_TIMEOUT);

	if (!ret) {
		dev_err(ctx->bdisp_dev->dev, "%s IRQ timeout\n", __func__);
		return -ETIMEDOUT;
	}

	return 0;
}
