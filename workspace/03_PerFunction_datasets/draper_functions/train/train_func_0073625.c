vbi_buffer_prepare(struct vb2_buffer *vb)
{
	struct au0828_dev *dev = vb2_get_drv_priv(vb->vb2_queue);
	unsigned long size;

	size = dev->vbi_width * dev->vbi_height * 2;

	if (vb2_plane_size(vb, 0) < size) {
		pr_err("%s data will not fit into plane (%lu < %lu)\n",
			__func__, vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}
	vb2_set_plane_payload(vb, 0, size);

	return 0;
}
