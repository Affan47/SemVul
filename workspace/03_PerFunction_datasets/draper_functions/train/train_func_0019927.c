keene_s_ctrl(struct v4l2_ctrl *ctrl)
{
	static const u8 db2tx[] = {

		0x03, 0x13, 0x02, 0x12, 0x22, 0x32,

		0x21, 0x31, 0x20, 0x30, 0x40, 0x50
	};
	struct keene_device *radio =
		container_of(ctrl->handler, struct keene_device, hdl);

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		radio->muted = ctrl->val;
		return keene_cmd_main(radio, 0, true);

	case V4L2_CID_TUNE_POWER_LEVEL:


		radio->pa = (ctrl->val - 71) * 100 / 62;
		return keene_cmd_main(radio, 0, true);

	case V4L2_CID_TUNE_PREEMPHASIS:
		radio->preemph_75_us = ctrl->val == V4L2_PREEMPHASIS_75_uS;
		return keene_cmd_set(radio);

	case V4L2_CID_AUDIO_COMPRESSION_GAIN:
		radio->tx = db2tx[(ctrl->val - (s32)ctrl->minimum) / (s32)ctrl->step];
		return keene_cmd_set(radio);
	}
	return -EINVAL;
}
