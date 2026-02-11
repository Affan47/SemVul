excel_read_CALCMODE (BiffQuery *q, GnmXLImporter *importer)
{
	XL_CHECK_CONDITION (q->length == 2);
	workbook_set_recalcmode (importer->wb,
				 GSF_LE_GET_GUINT16 (q->data) != 0);
}
