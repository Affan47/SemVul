exif_mnote_data_construct (ExifMnoteData *d, ExifMem *mem)
{
	if (!d || !mem) return;
	if (d->priv) return;
	d->priv = exif_mem_alloc (mem, sizeof (ExifMnoteDataPriv));
	if (!d->priv) return;

	d->priv->ref_count = 1;

	d->mem = mem;
	exif_mem_ref (mem);
}
