saa7146_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct saa7146_dev *dev = container_of(ctrl->handler,
				struct saa7146_dev, ctrl_handler);
	struct saa7146_vv *vv = dev->vv_data;
	u32 val;

	switch (ctrl->id) {
	case V4L2_CID_BRIGHTNESS:
		val = saa7146_read(dev, BCS_CTRL);
		val &= 0x00ffffff;
		val |= (ctrl->val << 24);
		saa7146_write(dev, BCS_CTRL, val);
		saa7146_write(dev, MC2, MASK_22 | MASK_06);
		break;

	case V4L2_CID_CONTRAST:
		val = saa7146_read(dev, BCS_CTRL);
		val &= 0xff00ffff;
		val |= (ctrl->val << 16);
		saa7146_write(dev, BCS_CTRL, val);
		saa7146_write(dev, MC2, MASK_22 | MASK_06);
		break;

	case V4L2_CID_SATURATION:
		val = saa7146_read(dev, BCS_CTRL);
		val &= 0xffffff00;
		val |= (ctrl->val << 0);
		saa7146_write(dev, BCS_CTRL, val);
		saa7146_write(dev, MC2, MASK_22 | MASK_06);
		break;

	case V4L2_CID_HFLIP:

		if ((vv->video_status & STATUS_CAPTURE))
			return -EBUSY;
		vv->hflip = ctrl->val;
		break;

	case V4L2_CID_VFLIP:
		if ((vv->video_status & STATUS_CAPTURE))
			return -EBUSY;
		vv->vflip = ctrl->val;
		break;

	default:
		return -EINVAL;
	}

	if ((vv->video_status & STATUS_OVERLAY) != 0) {
		struct saa7146_fh *fh = vv->video_fh;

		saa7146_stop_preview(fh);
		saa7146_start_preview(fh);
	}
	return 0;
}
