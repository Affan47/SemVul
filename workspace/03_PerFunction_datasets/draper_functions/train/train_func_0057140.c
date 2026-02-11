solo_enum_input(struct file *file, void *priv,
			   struct v4l2_input *input)
{
	struct solo_dev *solo_dev = video_drvdata(file);

	if (input->index >= solo_dev->nr_chans) {
		int ret = solo_enum_ext_input(solo_dev, input);

		if (ret < 0)
			return ret;
	} else {
		snprintf(input->name, sizeof(input->name), "Camera %d",
			 input->index + 1);


		if (!tw28_get_video_status(solo_dev, input->index))
			input->status = V4L2_IN_ST_NO_SIGNAL;
	}

	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->std = solo_dev->vfd->tvnorms;
	return 0;
}
