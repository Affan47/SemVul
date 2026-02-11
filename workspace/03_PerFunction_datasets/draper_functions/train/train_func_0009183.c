scg_paste_cellregion (SheetControlGUI *scg, double x, double y,
		      GnmCellRegion *content)
{
	WorkbookControl	*wbc  = scg_wbc (scg);
	Sheet *sheet = scg_sheet (scg) ;
	GnmPasteTarget pt;
	SheetObjectAnchor anchor;
	double coords[4];

	sheet_object_anchor_init (&anchor, NULL, NULL,
		GOD_ANCHOR_DIR_DOWN_RIGHT);
	coords[0] = coords[2] = x;
	coords[1] = coords[3] = y;
	scg_object_coords_to_anchor (scg, coords, &anchor);
	paste_target_init (&pt, sheet, &anchor.cell_bound, PASTE_ALL_TYPES);
	if (content && ((content->cols > 0 && content->rows > 0) ||
			content->objects != NULL))
		cmd_paste_copy (wbc, &pt, content);
}
