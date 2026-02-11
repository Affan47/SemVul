adv7343_setstd(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct adv7343_state *state = to_state(sd);
	struct adv7343_std_info *std_info;
	int num_std;
	char *fsc_ptr;
	u8 reg, val;
	int err = 0;
	int i = 0;

	std_info = (struct adv7343_std_info *)stdinfo;
	num_std = ARRAY_SIZE(stdinfo);

	for (i = 0; i < num_std; i++) {
		if (std_info[i].stdid & std)
			break;
	}

	if (i == num_std) {
		v4l2_dbg(1, debug, sd,
				"Invalid std or std is not supported: %llx\n",
						(unsigned long long)std);
		return -EINVAL;
	}


	val = state->reg80 & (~(SD_STD_MASK));
	val |= std_info[i].standard_val3;
	err = adv7343_write(sd, ADV7343_SD_MODE_REG1, val);
	if (err < 0)
		goto setstd_exit;

	state->reg80 = val;


	val = state->reg01 & (~((u8) INPUT_MODE_MASK));
	val |= SD_INPUT_MODE;
	err = adv7343_write(sd, ADV7343_MODE_SELECT_REG, val);
	if (err < 0)
		goto setstd_exit;

	state->reg01 = val;


	fsc_ptr = (unsigned char *)&std_info[i].fsc_val;
	reg = ADV7343_FSC_REG0;
	for (i = 0; i < 4; i++, reg++, fsc_ptr++) {
		err = adv7343_write(sd, reg, *fsc_ptr);
		if (err < 0)
			goto setstd_exit;
	}

	val = state->reg80;


	if (std & (V4L2_STD_NTSC | V4L2_STD_NTSC_443))
		val &= 0x03;
	else if (std & ~V4L2_STD_SECAM)
		val |= 0x04;

	err = adv7343_write(sd, ADV7343_SD_MODE_REG1, val);
	if (err < 0)
		goto setstd_exit;

	state->reg80 = val;

setstd_exit:
	if (err != 0)
		v4l2_err(sd, "Error setting std, write failed\n");

	return err;
}
