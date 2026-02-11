tvp514x_querystd(struct v4l2_subdev *sd, v4l2_std_id *std_id)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	enum tvp514x_std current_std;
	enum tvp514x_input input_sel;
	u8 sync_lock_status, lock_mask;

	if (std_id == NULL)
		return -EINVAL;


	if (!decoder->streaming) {
		tvp514x_s_stream(sd, 1);
		msleep(LOCK_RETRY_DELAY);
	}


	current_std = tvp514x_query_current_std(sd);
	if (current_std == STD_INVALID) {
		*std_id = V4L2_STD_UNKNOWN;
		return 0;
	}

	input_sel = decoder->input;

	switch (input_sel) {
	case INPUT_CVBS_VI1A:
	case INPUT_CVBS_VI1B:
	case INPUT_CVBS_VI1C:
	case INPUT_CVBS_VI2A:
	case INPUT_CVBS_VI2B:
	case INPUT_CVBS_VI2C:
	case INPUT_CVBS_VI3A:
	case INPUT_CVBS_VI3B:
	case INPUT_CVBS_VI3C:
	case INPUT_CVBS_VI4A:
		lock_mask = STATUS_CLR_SUBCAR_LOCK_BIT |
			STATUS_HORZ_SYNC_LOCK_BIT |
			STATUS_VIRT_SYNC_LOCK_BIT;
		break;

	case INPUT_SVIDEO_VI2A_VI1A:
	case INPUT_SVIDEO_VI2B_VI1B:
	case INPUT_SVIDEO_VI2C_VI1C:
	case INPUT_SVIDEO_VI2A_VI3A:
	case INPUT_SVIDEO_VI2B_VI3B:
	case INPUT_SVIDEO_VI2C_VI3C:
	case INPUT_SVIDEO_VI4A_VI1A:
	case INPUT_SVIDEO_VI4A_VI1B:
	case INPUT_SVIDEO_VI4A_VI1C:
	case INPUT_SVIDEO_VI4A_VI3A:
	case INPUT_SVIDEO_VI4A_VI3B:
	case INPUT_SVIDEO_VI4A_VI3C:
		lock_mask = STATUS_HORZ_SYNC_LOCK_BIT |
			STATUS_VIRT_SYNC_LOCK_BIT;
		break;

	default:
		return -EINVAL;
	}

	sync_lock_status = tvp514x_read_reg(sd, REG_STATUS1);
	if (lock_mask != (sync_lock_status & lock_mask)) {
		*std_id = V4L2_STD_UNKNOWN;
		return 0;
	}

	*std_id &= decoder->std_list[current_std].standard.id;

	v4l2_dbg(1, debug, sd, "Current STD: %s\n",
			decoder->std_list[current_std].standard.name);
	return 0;
}
