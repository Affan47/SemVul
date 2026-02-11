xtpg_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct xtpg_device *xtpg = container_of(ctrl->handler,
						struct xtpg_device,
						ctrl_handler);
	switch (ctrl->id) {
	case V4L2_CID_TEST_PATTERN:
		xvip_clr_and_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				 XTPG_PATTERN_MASK, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_CROSS_HAIRS:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_CROSS_HAIRS, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_MOVING_BOX:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_MOVING_BOX, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_COLOR_MASK:
		xvip_clr_and_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				 XTPG_PATTERN_CONTROL_COLOR_MASK_MASK,
				 ctrl->val <<
				 XTPG_PATTERN_CONTROL_COLOR_MASK_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_STUCK_PIXEL:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_STUCK_PIXEL, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_NOISE:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_NOISE, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_MOTION:
		xvip_clr_or_set(&xtpg->xvip, XTPG_PATTERN_CONTROL,
				XTPG_PATTERN_CONTROL_MOTION, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_MOTION_SPEED:
		xvip_write(&xtpg->xvip, XTPG_MOTION_SPEED, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_CROSS_HAIR_ROW:
		xvip_clr_and_set(&xtpg->xvip, XTPG_CROSS_HAIRS,
				 XTPG_CROSS_HAIRS_ROW_MASK,
				 ctrl->val << XTPG_CROSS_HAIRS_ROW_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_CROSS_HAIR_COLUMN:
		xvip_clr_and_set(&xtpg->xvip, XTPG_CROSS_HAIRS,
				 XTPG_CROSS_HAIRS_COLUMN_MASK,
				 ctrl->val << XTPG_CROSS_HAIRS_COLUMN_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_ZPLATE_HOR_START:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_HOR_CONTROL,
				 XTPG_ZPLATE_START_MASK,
				 ctrl->val << XTPG_ZPLATE_START_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_ZPLATE_HOR_SPEED:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_HOR_CONTROL,
				 XTPG_ZPLATE_SPEED_MASK,
				 ctrl->val << XTPG_ZPLATE_SPEED_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_ZPLATE_VER_START:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_VER_CONTROL,
				 XTPG_ZPLATE_START_MASK,
				 ctrl->val << XTPG_ZPLATE_START_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_ZPLATE_VER_SPEED:
		xvip_clr_and_set(&xtpg->xvip, XTPG_ZPLATE_VER_CONTROL,
				 XTPG_ZPLATE_SPEED_MASK,
				 ctrl->val << XTPG_ZPLATE_SPEED_SHIFT);
		return 0;
	case V4L2_CID_XILINX_TPG_BOX_SIZE:
		xvip_write(&xtpg->xvip, XTPG_BOX_SIZE, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_BOX_COLOR:
		xvip_write(&xtpg->xvip, XTPG_BOX_COLOR, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_STUCK_PIXEL_THRESH:
		xvip_write(&xtpg->xvip, XTPG_STUCK_PIXEL_THRESH, ctrl->val);
		return 0;
	case V4L2_CID_XILINX_TPG_NOISE_GAIN:
		xvip_write(&xtpg->xvip, XTPG_NOISE_GAIN, ctrl->val);
		return 0;
	}

	return 0;
}
