excel_read_FORMAT (BiffQuery *q, GnmXLImporter *importer)
{
	MsBiffVersion const ver = importer->ver;
	BiffFormatData *d;

	if (ver >= MS_BIFF_V7) {
		XL_CHECK_CONDITION (q->length >= 4);

		d = g_new (BiffFormatData, 1);
		d->idx = GSF_LE_GET_GUINT16 (q->data);
		d->name = (ver >= MS_BIFF_V8)
			? excel_biff_text_2 (importer, q, 2)
			: excel_biff_text_1 (importer, q, 2);
	} else {
		size_t minlen = (ver >= MS_BIFF_V4 ? 3 : 1);
		XL_CHECK_CONDITION (q->length >= minlen);

		d = g_new (BiffFormatData, 1);

		d->idx = g_hash_table_size (importer->format_table);
		d->name = (ver >= MS_BIFF_V4)
			? excel_biff_text_1 (importer, q, 2)
			: excel_biff_text_1 (importer, q, 0);
	}

	d (3, g_printerr ("Format data: 0x%x == '%s'\n", d->idx, d->name););

	g_hash_table_insert (importer->format_table, GUINT_TO_POINTER (d->idx), d);
}
