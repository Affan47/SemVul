brasero_iso9660_get_susp (BraseroIsoCtx *ctx,
			  BraseroIsoDirRec *record,
			  guint *susp_len)
{
	gchar *susp_block;
	gint start;
	gint len;

	start = sizeof (BraseroIsoDirRec) + record->id_size;

	if (start & 1)
		start ++;

	if (ctx->susp_skip)
		start += ctx->susp_skip;


	if (start >= record->record_size)
		return NULL;

	len = record->record_size - start;

	if (len <= 0)
		return NULL;

	if (susp_len)
		*susp_len = len;

	susp_block = ((gchar *) record) + start;

	BRASERO_MEDIA_LOG ("Got susp block");
	return susp_block;
}
