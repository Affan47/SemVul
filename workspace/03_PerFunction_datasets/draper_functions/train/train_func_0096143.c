cb_remote_names2 (GnmNamedExpr *nexpr,
		  G_GNUC_UNUSED gpointer value,
		  struct cb_remote_names *data)
{
	Workbook *wb =
		nexpr->pos.sheet ? nexpr->pos.sheet->workbook : nexpr->pos.wb;
	if (wb != data->wb)
		data->names = g_slist_prepend (data->names, nexpr);
}
