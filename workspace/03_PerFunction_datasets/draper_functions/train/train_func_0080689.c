formats_init (XLExportBase *ewb)
{
	int i;
	char const *fmt;

	ewb->formats.two_way_table
		= two_way_table_new (g_direct_hash, g_direct_equal, 0,
				     (GDestroyNotify)go_format_unref);


	for (i = 0; i < EXCEL_BUILTIN_FORMAT_LEN; i++) {
		fmt = excel_builtin_formats[i];
		if (!fmt || strlen (fmt) == 0)
			fmt = "General";
		two_way_table_put (ewb->formats.two_way_table,
				   go_format_new_from_XL (fmt),
				   FALSE,
				   (AfterPutFunc) after_put_format,
				   "Magic format %d - 0x%x\n");
	}
}
