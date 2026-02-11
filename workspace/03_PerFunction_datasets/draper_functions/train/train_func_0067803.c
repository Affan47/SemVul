exif_mnote_data_get_value (ExifMnoteData *d, unsigned int n, char *val, unsigned int maxlen)
{
	if (!d || !d->methods.get_value) return NULL;
	return d->methods.get_value (d, n, val, maxlen);
}
