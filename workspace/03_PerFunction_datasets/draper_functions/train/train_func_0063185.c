v4l1_radio_get_stereo(RadioDev *radio_dev)
{
	V4L1RadioDev *dev = (V4L1RadioDev*)radio_dev;
    struct video_audio va;
    va.mode=-1;

    if (dev->fd<0)
    	return -1;

    if (ioctl (dev->fd, VIDIOCGAUDIO, &va) < 0)
		return -1;
	if (va.mode == VIDEO_SOUND_STEREO)
		return 1;
	else
		return 0;
}
