vidioc_enum_input(struct file *file, void *priv,
				struct v4l2_input *input)
{
	struct gspca_dev *gspca_dev = video_drvdata(file);

	if (input->index != 0)
		return -EINVAL;
	input->type = V4L2_INPUT_TYPE_CAMERA;
	input->status = gspca_dev->cam.input_flags;
	strlcpy(input->name, gspca_dev->sd_desc->name,
		sizeof input->name);
	return 0;
}
