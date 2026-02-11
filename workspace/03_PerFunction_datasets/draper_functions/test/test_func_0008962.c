workbook_attach_view (WorkbookView *wbv)
{
	Workbook *wb;

	g_return_if_fail (IS_WORKBOOK_VIEW (wbv));

	wb = wb_view_get_workbook (wbv);
	g_return_if_fail (IS_WORKBOOK (wb));

	if (wb->wb_views == NULL)
		wb->wb_views = g_ptr_array_new ();
	g_ptr_array_add (wb->wb_views, wbv);
}
