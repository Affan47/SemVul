lut_ioctl(struct v4l2_subdev *subdev, unsigned int cmd, void *arg)
{
	struct vsp1_lut *lut = to_lut(subdev);

	switch (cmd) {
	case VIDIOC_VSP1_LUT_CONFIG:
		lut_configure(lut, arg);
		return 0;

	default:
		return -ENOIOCTLCMD;
	}
}
