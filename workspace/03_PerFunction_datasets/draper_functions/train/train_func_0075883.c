noon010_power_ctrl(struct v4l2_subdev *sd, bool reset, bool sleep)
{
	struct noon010_info *info = to_noon010(sd);
	u8 reg = sleep ? 0xF1 : 0xF0;
	int ret = 0;

	if (reset) {
		ret = cam_i2c_write(sd, POWER_CTRL_REG, reg | 0x02);
		udelay(20);
	}
	if (!ret) {
		ret = cam_i2c_write(sd, POWER_CTRL_REG, reg);
		if (reset && !ret)
			info->i2c_reg_page = -1;
	}
	return ret;
}
