excel_read_BG_PIC (BiffQuery *q,
		   ExcelReadSheet *esheet)
{

	GdkPixbuf *background = excel_read_IMDATA (q, TRUE);
	if (background != NULL)
		g_object_unref (background);
}
