adv7393_setoutput(struct v4l2_subdev *sd, u32 output_type)
{
	struct adv7393_state *state = to_state(sd);
	u8 val;
	int err = 0;

	if (output_type > ADV7393_SVIDEO_ID) {
		v4l2_dbg(1, debug, sd,
			"Invalid output type or output type not supported:%d\n",
								output_type);
		return -EINVAL;
	}


	val = state->reg00 & 0x03;

	if (output_type == ADV7393_COMPOSITE_ID)
		val |= ADV7393_COMPOSITE_POWER_VALUE;
	else if (output_type == ADV7393_COMPONENT_ID)
		val |= ADV7393_COMPONENT_POWER_VALUE;
	else
		val |= ADV7393_SVIDEO_POWER_VALUE;

	err = adv7393_write(sd, ADV7393_POWER_MODE_REG, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg00 = val;


	val = state->reg02 | YUV_OUTPUT_SELECT;
	err = adv7393_write(sd, ADV7393_MODE_REG0, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg02 = val;


	val = state->reg82;
	if (output_type == ADV7393_COMPONENT_ID)
		val &= SD_DAC_OUT1_DI;
	else
		val |= SD_DAC_OUT1_EN;
	err = adv7393_write(sd, ADV7393_SD_MODE_REG2, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg82 = val;


	val = state->reg35 & HD_DAC_SWAP_DI;
	err = adv7393_write(sd, ADV7393_HD_MODE_REG6, val);
	if (err < 0)
		goto setoutput_exit;

	state->reg35 = val;

setoutput_exit:
	if (err != 0)
		v4l2_err(sd, "Error setting output, write failed\n");

	return err;
}
