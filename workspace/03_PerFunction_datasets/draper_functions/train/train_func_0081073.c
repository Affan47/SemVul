bttv_querycap(struct file *file, void  *priv,
				struct v4l2_capability *cap)
{
	struct video_device *vdev = video_devdata(file);
	struct bttv_fh *fh = priv;
	struct bttv *btv = fh->btv;

	if (0 == v4l2)
		return -EINVAL;

	strlcpy(cap->driver, "bttv", sizeof(cap->driver));
	strlcpy(cap->card, btv->video_dev.name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "PCI:%s", pci_name(btv->c.pci));
	cap->capabilities =
		V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_READWRITE |
		V4L2_CAP_STREAMING |
		V4L2_CAP_DEVICE_CAPS;
	if (no_overlay <= 0)
		cap->capabilities |= V4L2_CAP_VIDEO_OVERLAY;
	if (video_is_registered(&btv->vbi_dev))
		cap->capabilities |= V4L2_CAP_VBI_CAPTURE;
	if (video_is_registered(&btv->radio_dev))
		cap->capabilities |= V4L2_CAP_RADIO;


	if (btv->has_saa6588)
		cap->capabilities |= V4L2_CAP_RDS_CAPTURE;
	if (btv->tuner_type != TUNER_ABSENT)
		cap->capabilities |= V4L2_CAP_TUNER;
	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		cap->device_caps = cap->capabilities &
			(V4L2_CAP_VIDEO_CAPTURE |
			 V4L2_CAP_READWRITE |
			 V4L2_CAP_STREAMING |
			 V4L2_CAP_VIDEO_OVERLAY |
			 V4L2_CAP_TUNER);
	else if (vdev->vfl_type == VFL_TYPE_VBI)
		cap->device_caps = cap->capabilities &
			(V4L2_CAP_VBI_CAPTURE |
			 V4L2_CAP_READWRITE |
			 V4L2_CAP_STREAMING |
			 V4L2_CAP_TUNER);
	else {
		cap->device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		if (btv->has_saa6588)
			cap->device_caps |= V4L2_CAP_READWRITE |
						V4L2_CAP_RDS_CAPTURE;
		if (btv->has_tea575x)
			cap->device_caps |= V4L2_CAP_HW_FREQ_SEEK;
	}
	return 0;
}
