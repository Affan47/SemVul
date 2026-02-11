m5mols_set_exposure(struct m5mols_info *info, int exposure)
{
	struct v4l2_subdev *sd = &info->sd;
	int ret = 0;

	if (exposure == V4L2_EXPOSURE_AUTO) {

		info->lock_3a->val &= ~V4L2_LOCK_EXPOSURE;
		m5mols_3a_lock(info, info->lock_3a);

		ret = m5mols_set_metering_mode(info, info->metering->val);
		if (ret < 0)
			return ret;

		v4l2_dbg(1, m5mols_debug, sd,
			 "%s: exposure bias: %#x, metering: %#x\n",
			 __func__, info->exposure_bias->val,
			 info->metering->val);

		return m5mols_write(sd, AE_INDEX, info->exposure_bias->val);
	}

	if (exposure == V4L2_EXPOSURE_MANUAL) {
		ret = m5mols_write(sd, AE_MODE, REG_AE_OFF);
		if (ret == 0)
			ret = m5mols_write(sd, AE_MAN_GAIN_MON,
					   info->exposure->val);
		if (ret == 0)
			ret = m5mols_write(sd, AE_MAN_GAIN_CAP,
					   info->exposure->val);

		v4l2_dbg(1, m5mols_debug, sd, "%s: exposure: %#x\n",
			 __func__, info->exposure->val);
	}

	return ret;
}
