pvr2_streamoff(struct file *file, void *priv, enum v4l2_buf_type i)
{
	struct pvr2_v4l2_fh *fh = file->private_data;
	struct pvr2_hdw *hdw = fh->channel.mc_head->hdw;

	if (!fh->pdi->stream) {


		return -EPERM;
	}
	return pvr2_hdw_set_streaming(hdw, 0);
}
