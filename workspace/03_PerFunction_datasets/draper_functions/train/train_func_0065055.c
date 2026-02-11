ov6550_g_volatile_ctrl(struct v4l2_ctrl *ctrl)
{
	struct ov6650 *priv = container_of(ctrl->handler, struct ov6650, hdl);
	struct v4l2_subdev *sd = &priv->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	uint8_t reg, reg2;
	int ret;

	switch (ctrl->id) {
	case V4L2_CID_AUTOGAIN:
		ret = ov6650_reg_read(client, REG_GAIN, &reg);
		if (!ret)
			priv->gain->val = reg;
		return ret;
	case V4L2_CID_AUTO_WHITE_BALANCE:
		ret = ov6650_reg_read(client, REG_BLUE, &reg);
		if (!ret)
			ret = ov6650_reg_read(client, REG_RED, &reg2);
		if (!ret) {
			priv->blue->val = reg;
			priv->red->val = reg2;
		}
		return ret;
	case V4L2_CID_EXPOSURE_AUTO:
		ret = ov6650_reg_read(client, REG_AECH, &reg);
		if (!ret)
			priv->exposure->val = reg;
		return ret;
	}
	return -EINVAL;
}
