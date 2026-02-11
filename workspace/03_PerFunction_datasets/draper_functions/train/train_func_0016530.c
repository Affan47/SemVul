vidioc_g_audinput(struct file *file, void *priv,
	struct v4l2_audio *i)
{
	struct cx23885_dev *dev = video_drvdata(file);

	if ((CX23885_VMUX_TELEVISION == INPUT(dev->input)->type) ||
		(CX23885_VMUX_CABLE == INPUT(dev->input)->type))
		i->index = 2;
	else
		i->index = dev->audinput;
	dprintk(1, "%s(input=%d)\n", __func__, i->index);

	return cx23885_query_audinput(file, priv, i);
}
