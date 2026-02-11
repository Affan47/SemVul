sh_vou_buf_prepare(struct vb2_buffer *vb)
{
	struct sh_vou_device *vou_dev = vb2_get_drv_priv(vb->vb2_queue);
	struct v4l2_pix_format *pix = &vou_dev->pix;
	unsigned bytes_per_line = vou_fmt[vou_dev->pix_idx].bpp * pix->width / 8;
	unsigned size = pix->height * bytes_per_line;

	dev_dbg(vou_dev->v4l2_dev.dev, "%s()\n", __func__);

	if (vb2_plane_size(vb, 0) < size) {

		dev_warn(vou_dev->v4l2_dev.dev, "buffer too small (%lu < %u)\n",
			 vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}

	vb2_set_plane_payload(vb, 0, size);
	return 0;
}
