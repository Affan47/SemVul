start_new_row(struct sonly_dev *sdev, unsigned char *data, int size)
{
	if (!sdev->rowbuf)
		sdev->rowbuf = g_malloc(IMG_WIDTH);
	memcpy(sdev->rowbuf, data, size);
	sdev->rowbuf_offset = size;
}
