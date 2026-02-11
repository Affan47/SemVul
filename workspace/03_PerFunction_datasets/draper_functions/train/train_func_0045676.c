vidioc_enumaudio(struct file *file, void *fh, struct v4l2_audio *a)
{
	dprintk(2, "VIDIOC_G_AUDIO: %d\n", a->index);
	if (a->index != 0)
		return -EINVAL;
	*a = msp3400_v4l2_audio;
	return 0;
}
