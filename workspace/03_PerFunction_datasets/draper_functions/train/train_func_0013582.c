s5k4ecgx_init_v4l2_ctrls(struct s5k4ecgx *priv)
{
	const struct v4l2_ctrl_ops *ops = &s5k4ecgx_ctrl_ops;
	struct v4l2_ctrl_handler *hdl = &priv->handler;
	int ret;

	ret = v4l2_ctrl_handler_init(hdl, 4);
	if (ret)
		return ret;

	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_BRIGHTNESS, -208, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_CONTRAST, -127, 127, 1, 0);
	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SATURATION, -127, 127, 1, 0);


	v4l2_ctrl_new_std(hdl, ops, V4L2_CID_SHARPNESS, -32704/SHARPNESS_DIV,
			  24612/SHARPNESS_DIV, 1, 2);
	if (hdl->error) {
		ret = hdl->error;
		v4l2_ctrl_handler_free(hdl);
		return ret;
	}
	priv->sd.ctrl_handler = hdl;

	return 0;
}
