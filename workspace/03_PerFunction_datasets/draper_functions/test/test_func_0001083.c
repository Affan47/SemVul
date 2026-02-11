g2d_setup_ctrls(struct g2d_ctx *ctx)
{
	struct g2d_dev *dev = ctx->dev;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, 3);

	ctx->ctrl_hflip = v4l2_ctrl_new_std(&ctx->ctrl_handler, &g2d_ctrl_ops,
						V4L2_CID_HFLIP, 0, 1, 1, 0);

	ctx->ctrl_vflip = v4l2_ctrl_new_std(&ctx->ctrl_handler, &g2d_ctrl_ops,
						V4L2_CID_VFLIP, 0, 1, 1, 0);

	v4l2_ctrl_new_std_menu(
		&ctx->ctrl_handler,
		&g2d_ctrl_ops,
		V4L2_CID_COLORFX,
		V4L2_COLORFX_NEGATIVE,
		~((1 << V4L2_COLORFX_NONE) | (1 << V4L2_COLORFX_NEGATIVE)),
		V4L2_COLORFX_NONE);

	if (ctx->ctrl_handler.error) {
		int err = ctx->ctrl_handler.error;
		v4l2_err(&dev->v4l2_dev, "g2d_setup_ctrls failed\n");
		v4l2_ctrl_handler_free(&ctx->ctrl_handler);
		return err;
	}

	v4l2_ctrl_cluster(2, &ctx->ctrl_hflip);

	return 0;
}
