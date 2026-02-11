sh_veu_is_streamer(struct sh_veu_dev *veu, struct sh_veu_file *veu_file,
			       enum v4l2_buf_type type)
{
	return (type == V4L2_BUF_TYPE_VIDEO_CAPTURE &&
		veu_file == veu->capture) ||
		(type == V4L2_BUF_TYPE_VIDEO_OUTPUT &&
		 veu_file == veu->output);
}
