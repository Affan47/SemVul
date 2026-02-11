comment_view_button2_pressed (GocItem *item, int button, double x, double y)
{
	SheetObject *so;
	GnmRange const *r;
	SheetControlGUI *scg;
	if (button !=1)
		return FALSE;

	scg = GNM_PANE (item->canvas)->simple.scg;
	so = sheet_object_view_get_so (SHEET_OBJECT_VIEW (item));
	r = sheet_object_get_range (so);
	dialog_cell_comment (scg->wbcg, so->sheet, &r->start);
	return TRUE;
}
