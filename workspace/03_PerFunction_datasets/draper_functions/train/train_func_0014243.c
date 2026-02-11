excel_write_obj_v8 (ExcelWriteSheet *esheet, SheetObject *so)
{
	if (IS_SHEET_OBJECT_GRAPH (so))
		return excel_write_chart_v8 (esheet, so);
	if (IS_GNM_SO_LINE (so))
		return excel_write_line_v8 (esheet, so);
	return excel_write_other_v8 (esheet, so);
}
