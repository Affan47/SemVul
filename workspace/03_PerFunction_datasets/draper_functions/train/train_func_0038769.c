s2250_log_status(struct v4l2_subdev *sd)
{
	struct s2250 *state = to_state(sd);

	v4l2_info(sd, "Standard: %s\n", state->std == V4L2_STD_NTSC ? "NTSC" :
					state->std == V4L2_STD_PAL ? "PAL" :
					state->std == V4L2_STD_SECAM ? "SECAM" :
					"unknown");
	v4l2_info(sd, "Input: %s\n", state->input == 0 ? "Composite" :
					state->input == 1 ? "S-video" :
					"error");
	v4l2_info(sd, "Audio input: %s\n", state->audio_input == 0 ? "Line In" :
					state->audio_input == 1 ? "Mic" :
					state->audio_input == 2 ? "Mic Boost" :
					"error");
	return v4l2_ctrl_subdev_log_status(sd);
}
