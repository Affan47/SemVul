msp_log_status(struct v4l2_subdev *sd)
{
	struct msp_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	const char *p;
	char prefix[V4L2_SUBDEV_NAME_SIZE + 20];

	if (state->opmode == OPMODE_AUTOSELECT)
		msp_detect_stereo(client);
	v4l_info(client, "%s rev1 = 0x%04x rev2 = 0x%04x\n",
			client->name, state->rev1, state->rev2);
	snprintf(prefix, sizeof(prefix), "%s: Audio:    ", sd->name);
	v4l2_ctrl_handler_log_status(&state->hdl, prefix);
	switch (state->mode) {
		case MSP_MODE_AM_DETECT: p = "AM (for carrier detect)"; break;
		case MSP_MODE_FM_RADIO: p = "FM Radio"; break;
		case MSP_MODE_FM_TERRA: p = "Terrestrial FM-mono/stereo"; break;
		case MSP_MODE_FM_SAT: p = "Satellite FM-mono"; break;
		case MSP_MODE_FM_NICAM1: p = "NICAM/FM (B/G, D/K)"; break;
		case MSP_MODE_FM_NICAM2: p = "NICAM/FM (I)"; break;
		case MSP_MODE_AM_NICAM: p = "NICAM/AM (L)"; break;
		case MSP_MODE_BTSC: p = "BTSC"; break;
		case MSP_MODE_EXTERN: p = "External input"; break;
		default: p = "unknown"; break;
	}
	if (state->mode == MSP_MODE_EXTERN) {
		v4l_info(client, "Mode:     %s\n", p);
	} else if (state->opmode == OPMODE_MANUAL) {
		v4l_info(client, "Mode:     %s (%s%s)\n", p,
				(state->rxsubchans & V4L2_TUNER_SUB_STEREO) ? "stereo" : "mono",
				(state->rxsubchans & V4L2_TUNER_SUB_LANG2) ? ", dual" : "");
	} else {
		if (state->opmode == OPMODE_AUTODETECT)
			v4l_info(client, "Mode:     %s\n", p);
		v4l_info(client, "Standard: %s (%s%s)\n",
				msp_standard_std_name(state->std),
				(state->rxsubchans & V4L2_TUNER_SUB_STEREO) ? "stereo" : "mono",
				(state->rxsubchans & V4L2_TUNER_SUB_LANG2) ? ", dual" : "");
	}
	v4l_info(client, "Audmode:  0x%04x\n", state->audmode);
	v4l_info(client, "Routing:  0x%08x (input) 0x%08x (output)\n",
			state->route_in, state->route_out);
	v4l_info(client, "ACB:      0x%04x\n", state->acb);
	return 0;
}
