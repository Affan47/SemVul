ad9389b_check_edid_status(struct v4l2_subdev *sd)
{
	struct ad9389b_state *state = get_ad9389b_state(sd);
	struct ad9389b_edid_detect ed;
	int segment;
	u8 edidRdy = ad9389b_rd(sd, 0xc5);

	v4l2_dbg(1, debug, sd, "%s: edid ready (retries: %d)\n",
		 __func__, EDID_MAX_RETRIES - state->edid.read_retries);

	if (!(edidRdy & MASK_AD9389B_EDID_RDY))
		return false;

	segment = ad9389b_rd(sd, 0xc4);
	if (segment >= EDID_MAX_SEGM) {
		v4l2_err(sd, "edid segment number too big\n");
		return false;
	}
	v4l2_dbg(1, debug, sd, "%s: got segment %d\n", __func__, segment);
	ad9389b_edid_rd(sd, 256, &state->edid.data[segment * 256]);
	ad9389b_dbg_dump_edid(2, debug, sd, segment,
			      &state->edid.data[segment * 256]);
	if (segment == 0) {
		state->edid.blocks = state->edid.data[0x7e] + 1;
		v4l2_dbg(1, debug, sd, "%s: %d blocks in total\n",
			 __func__, state->edid.blocks);
	}
	if (!edid_verify_crc(sd, segment) ||
	    !edid_verify_header(sd, segment)) {

		v4l2_err(sd, "%s: edid crc or header error\n", __func__);
		ad9389b_s_power(sd, false);
		ad9389b_s_power(sd, true);
		return false;
	}

	state->edid.segments = segment + 1;
	if (((state->edid.data[0x7e] >> 1) + 1) > state->edid.segments) {

		v4l2_dbg(1, debug, sd, "%s: request segment %d\n",
			 __func__, state->edid.segments);
		ad9389b_wr(sd, 0xc9, 0xf);
		ad9389b_wr(sd, 0xc4, state->edid.segments);
		state->edid.read_retries = EDID_MAX_RETRIES;
		queue_delayed_work(state->work_queue,
				   &state->edid_handler, EDID_DELAY);
		return false;
	}


	ed.present = true;
	ed.segment = 0;
	v4l2_subdev_notify(sd, AD9389B_EDID_DETECT, (void *)&ed);
	state->edid_detect_counter++;
	v4l2_ctrl_s_ctrl(state->have_edid0_ctrl, state->edid.segments ? 0x1 : 0x0);
	return ed.present;
}
