saa7164_g_tuner(struct file *file, void *priv, struct v4l2_tuner *t)
{
	struct saa7164_encoder_fh *fh = file->private_data;
	struct saa7164_port *port = fh->port;
	struct saa7164_dev *dev = port->dev;

	if (0 != t->index)
		return -EINVAL;

	strcpy(t->name, "tuner");
	t->capability = V4L2_TUNER_CAP_NORM | V4L2_TUNER_CAP_STEREO;
	t->rangelow = SAA7164_TV_MIN_FREQ;
	t->rangehigh = SAA7164_TV_MAX_FREQ;

	dprintk(DBGLVL_ENC, "VIDIOC_G_TUNER: tuner type %d\n", t->type);

	return 0;
}
