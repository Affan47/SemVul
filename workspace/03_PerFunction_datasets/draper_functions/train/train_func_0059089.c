m5mols_read_u32(struct v4l2_subdev *sd, u32 reg, u32 *val)
{
	if (I2C_SIZE(reg) != 4) {
		v4l2_err(sd, "Wrong data size\n");
		return -EINVAL;
	}

	return m5mols_read(sd, I2C_SIZE(reg), reg, val);
}
