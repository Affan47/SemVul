adv7842_set_gain(struct v4l2_subdev *sd, bool auto_gain, u16 gain_a, u16 gain_b, u16 gain_c)
{
	struct adv7842_state *state = to_state(sd);
	u8 gain_buf[4];
	u8 gain_man = 1;
	u8 agc_mode_man = 1;

	if (auto_gain) {
		gain_man = 0;
		agc_mode_man = 0;
		gain_a = 0x100;
		gain_b = 0x100;
		gain_c = 0x100;
	}

	v4l2_dbg(2, debug, sd, "%s: %s gain: a = 0x%x, b = 0x%x, c = 0x%x\n",
		 __func__, auto_gain ? "Auto" : "Manual",
		 gain_a, gain_b, gain_c);

	gain_buf[0] = ((gain_man << 7) | (agc_mode_man << 6) | ((gain_a & 0x3f0) >> 4));
	gain_buf[1] = (((gain_a & 0x00f) << 4) | ((gain_b & 0x3c0) >> 6));
	gain_buf[2] = (((gain_b & 0x03f) << 2) | ((gain_c & 0x300) >> 8));
	gain_buf[3] = ((gain_c & 0x0ff));


	if (adv_smbus_write_i2c_block_data(state->i2c_cp, 0x73, 4, gain_buf))
		v4l2_err(sd, "%s: i2c error writing to CP reg 0x73, 0x74, 0x75, 0x76\n", __func__);
}
