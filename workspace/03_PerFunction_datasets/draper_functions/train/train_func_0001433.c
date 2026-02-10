vidioc_s_input(struct file *file, void *fh, unsigned int input)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_S_INPUT: %d\n", input);

	if (!av7110->analog_tuner_flags)
		return input ? -EINVAL : 0;

	if (input >= 4)
		return -EINVAL;

	av7110->current_input = input;
	return av7110_dvb_c_switch(fh);
}
