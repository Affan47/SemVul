mma9551_read_incli_chan(struct i2c_client *client,
				   const struct iio_chan_spec *chan,
				   int *val)
{
	u8 quad_shift, angle, quadrant;
	u16 reg_addr;
	int ret;

	switch (chan->channel2) {
	case IIO_MOD_X:
		reg_addr = MMA9551_TILT_YZ_ANG_REG;
		quad_shift = MMA9551_TILT_YZ_QUAD_SHIFT;
		break;
	case IIO_MOD_Y:
		reg_addr = MMA9551_TILT_XZ_ANG_REG;
		quad_shift = MMA9551_TILT_XZ_QUAD_SHIFT;
		break;
	case IIO_MOD_Z:
		reg_addr = MMA9551_TILT_XY_ANG_REG;
		quad_shift = MMA9551_TILT_XY_QUAD_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	ret = mma9551_set_power_state(client, true);
	if (ret < 0)
		return ret;

	ret = mma9551_read_status_byte(client, MMA9551_APPID_TILT,
				       reg_addr, &angle);
	if (ret < 0)
		goto out_poweroff;

	ret = mma9551_read_status_byte(client, MMA9551_APPID_TILT,
				       MMA9551_TILT_QUAD_REG, &quadrant);
	if (ret < 0)
		goto out_poweroff;

	angle &= ~MMA9551_TILT_ANGFLG;
	quadrant = (quadrant >> quad_shift) & 0x03;

	if (quadrant == 1 || quadrant == 3)
		*val = 90 * (quadrant + 1) - angle;
	else
		*val = angle + 90 * quadrant;

	ret = IIO_VAL_INT;

out_poweroff:
	mma9551_set_power_state(client, false);
	return ret;
}
