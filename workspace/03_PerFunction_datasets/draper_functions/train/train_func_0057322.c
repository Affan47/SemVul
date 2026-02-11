exif_loader_copy (ExifLoader *eld, unsigned char *buf, unsigned int len)
{
	if (!eld || (len && !buf) || (eld->bytes_read >= eld->size))
		return 0;


	if (!eld->buf)
		eld->buf = exif_loader_alloc (eld, eld->size);
	if (!eld->buf)
		return 0;


	len = MIN (len, eld->size - eld->bytes_read);
	memcpy (eld->buf + eld->bytes_read, buf, len);
	eld->bytes_read += len;

	return (eld->bytes_read >= eld->size) ? 0 : 1;
}
