wb_view_detach_from_workbook (WorkbookView *wbv)
{
	g_return_if_fail (IS_WORKBOOK_VIEW (wbv));

	if (wbv->wb) {
		workbook_detach_view (wbv);
		wbv->wb = NULL;
		wbv->current_sheet = NULL;
	}
}
