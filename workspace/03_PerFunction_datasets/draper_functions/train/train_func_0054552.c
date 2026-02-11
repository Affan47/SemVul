gnm_sheet_slicer_set_sheet (GnmSheetSlicer *gss, Sheet *sheet)
{
	g_return_if_fail (IS_SHEET (sheet));
	g_return_if_fail (IS_GNM_SHEET_SLICER (gss));
	g_return_if_fail (NULL == gss->sheet);

	g_object_ref (gss);
	gss->sheet = sheet;
	sheet->slicers = g_slist_prepend (sheet->slicers, gss);
}
