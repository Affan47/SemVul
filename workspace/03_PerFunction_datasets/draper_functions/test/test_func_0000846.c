vidioc_g_tuner(struct file *file, void *priv, struct v4l2_tuner *t)
{
	struct au0828_dev *dev = video_drvdata(file);

	if (t->index != 0)
		return -EINVAL;

	dprintk(1, "%s called std_set %d dev_state %ld\n", __func__,
		dev->std_set_in_tuner_core, dev->dev_state);

	strcpy(t->name, "Auvitek tuner");

	au0828_init_tuner(dev);
	i2c_gate_ctrl(dev, 1);
	v4l2_device_call_all(&dev->v4l2_dev, 0, tuner, g_tuner, t);
	i2c_gate_ctrl(dev, 0);
	return 0;
}
