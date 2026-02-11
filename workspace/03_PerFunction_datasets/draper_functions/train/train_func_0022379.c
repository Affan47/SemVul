saa6752hs_try_ctrl(struct v4l2_ctrl *ctrl)
{
	struct saa6752hs_state *h =
		container_of(ctrl->handler, struct saa6752hs_state, hdl);

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_BITRATE_MODE:

		if (ctrl->val == V4L2_MPEG_VIDEO_BITRATE_MODE_VBR &&
		    h->video_bitrate_peak->val < h->video_bitrate->val)
			h->video_bitrate_peak->val = h->video_bitrate->val;
		break;
	}
	return 0;
}
