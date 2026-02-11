buffer_queue(struct videobuf_queue *q, struct videobuf_buffer *vb)
{
	struct file *file = q->priv_data;
	struct saa7146_fh *fh = file->private_data;
	struct saa7146_dev *dev = fh->dev;
	struct saa7146_vv *vv = dev->vv_data;
	struct saa7146_buf *buf = (struct saa7146_buf *)vb;

	DEB_VBI("vb:%p\n", vb);
	saa7146_buffer_queue(dev, &vv->vbi_dmaq, buf);
}
