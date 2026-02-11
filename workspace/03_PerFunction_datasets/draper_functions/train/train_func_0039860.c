excel_read_XF_INDEX (BiffQuery *q, ExcelReadSheet *esheet)
{
	XL_CHECK_CONDITION (q->length >= 2);
	esheet->biff2_prev_xf_index = GSF_LE_GET_GUINT16 (q->data);
}
