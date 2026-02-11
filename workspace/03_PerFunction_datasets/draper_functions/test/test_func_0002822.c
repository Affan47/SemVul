vivid_raw_vbi_cap_process(struct vivid_dev *dev, struct vivid_buffer *buf)
{
	struct v4l2_vbi_format vbi;
	u8 *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	vivid_g_fmt_vbi_cap(dev, &vbi);
	buf->vb.sequence = dev->vbi_cap_seq_count;
	if (dev->field_cap == V4L2_FIELD_ALTERNATE)
		buf->vb.sequence /= 2;

	vivid_sliced_vbi_cap_fill(dev, buf->vb.sequence);

	memset(vbuf, 0x10, vb2_plane_size(&buf->vb.vb2_buf, 0));

	if (!VIVID_INVALID_SIGNAL(dev->std_signal_mode))
		vivid_vbi_gen_raw(&dev->vbi_gen, &vbi, vbuf);

	v4l2_get_timestamp(&buf->vb.timestamp);
	buf->vb.timestamp.tv_sec += dev->time_wrap_offset;
}
