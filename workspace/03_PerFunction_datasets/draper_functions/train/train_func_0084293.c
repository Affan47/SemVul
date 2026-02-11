record_new (XBfile *file)
{
	XBrecord *ans = g_new (XBrecord, 1);
	ans->file = file;
	ans->row = 1;

	ans->data = (guint8 *) g_strnfill (file->fieldlen, '?');
	record_seek (ans, SEEK_SET, 1);
	return ans;
}
