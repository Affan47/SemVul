pvr2_s_input(struct file *file, void *priv, unsigned int inp)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	if (inp >= fh->input_cnt)
		return -EINVAL;
	return pvr2_ctrl_set_value(
			pvr2_hdw_get_ctrl_by_id(hdw, PVR2_CID_INPUT),
			fh->input_map[inp]);
}
