control_point_button2_pressed (GocItem *item, int button, G_GNUC_UNUSED double x, G_GNUC_UNUSED double y)
{
	GnmPane *pane = GNM_PANE (item->canvas);
	SheetControlGUI *scg = pane->simple.scg;
	SheetObject *so;

	so  = g_object_get_data (G_OBJECT (item), "so");
	if (pane->drag.button == 1)
		sheet_object_get_editor (so, SHEET_CONTROL (scg));
	return TRUE;
}
