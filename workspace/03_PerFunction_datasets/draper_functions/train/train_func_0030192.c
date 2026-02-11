pvr2_g_crop(struct file *file, void *priv, struct v4l2_crop *crop)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;
	int val = 0;
	int ret;

	if (crop->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPL), &val);
	if (ret != 0)
		return -EINVAL;
	crop->c.left = val;
	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPT), &val);
	if (ret != 0)
		return -EINVAL;
	crop->c.top = val;
	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPW), &val);
	if (ret != 0)
		return -EINVAL;
	crop->c.width = val;
	ret = pvr2_ctrl_get_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_CROPH), &val);
	if (ret != 0)
		return -EINVAL;
	crop->c.height = val;
	return 0;
}
