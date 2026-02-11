cx2341x_ext_ctrls(struct cx2341x_mpeg_params *params, int busy,
		  struct v4l2_ext_controls *ctrls, unsigned int cmd)
{
	int err = 0;
	int i;

	if (cmd == VIDIOC_G_EXT_CTRLS) {
		for (i = 0; i < ctrls->count; i++) {
			struct v4l2_ext_control *ctrl = ctrls->controls + i;

			err = cx2341x_get_ctrl(params, ctrl);
			if (err) {
				ctrls->error_idx = i;
				break;
			}
		}
		return err;
	}
	for (i = 0; i < ctrls->count; i++) {
		struct v4l2_ext_control *ctrl = ctrls->controls + i;
		struct v4l2_queryctrl qctrl;
		const char * const *menu_items = NULL;

		qctrl.id = ctrl->id;
		err = cx2341x_ctrl_query(params, &qctrl);
		if (err)
			break;
		if (qctrl.type == V4L2_CTRL_TYPE_MENU)
			menu_items = cx2341x_ctrl_get_menu(params, qctrl.id);
		err = v4l2_ctrl_check(ctrl, &qctrl, menu_items);
		if (err)
			break;
		err = cx2341x_set_ctrl(params, busy, ctrl);
		if (err)
			break;
	}
	if (err == 0 &&
	    params->video_bitrate_mode == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
	    params->video_bitrate_peak < params->video_bitrate) {
		err = -ERANGE;
		ctrls->error_idx = ctrls->count;
	}
	if (err)
		ctrls->error_idx = i;
	else
		cx2341x_calc_audio_properties(params);
	return err;
}
