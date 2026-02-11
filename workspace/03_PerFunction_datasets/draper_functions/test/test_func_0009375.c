scg_object_anchor_to_coords (SheetControlGUI const *scg,
			     SheetObjectAnchor const *anchor, double *coords)
{
	Sheet *sheet = scg_sheet (scg);
	GODrawingAnchorDir direction;
	gint64 pixels[4];
	GnmRange const *r;

	g_return_if_fail (IS_SHEET_CONTROL_GUI (scg));
	g_return_if_fail (anchor != NULL);
	g_return_if_fail (coords != NULL);

	r = &anchor->cell_bound;
	pixels[0] = scg_colrow_distance_get (scg, TRUE, 0,  r->start.col);
	pixels[2] = pixels[0] + scg_colrow_distance_get (scg, TRUE,
		r->start.col, r->end.col);
	pixels[1] = scg_colrow_distance_get (scg, FALSE, 0, r->start.row);
	pixels[3] = pixels[1] + scg_colrow_distance_get (scg, FALSE,
		r->start.row, r->end.row);

	pixels[0] += cell_offset_calc_pixel (sheet, r->start.col,
		TRUE, anchor->offset[0]) + .5;
	pixels[1] += cell_offset_calc_pixel (sheet, r->start.row,
		FALSE, anchor->offset[1]) + .5;
	pixels[2] += cell_offset_calc_pixel (sheet, r->end.col,
		TRUE, anchor->offset[2]) + .5;
	pixels[3] += cell_offset_calc_pixel (sheet, r->end.row,
		FALSE, anchor->offset[3]) + .5;

	direction = anchor->base.direction;
	if (direction == GOD_ANCHOR_DIR_UNKNOWN)
		direction = GOD_ANCHOR_DIR_DOWN_RIGHT;

	coords[0] = pixels[direction & GOD_ANCHOR_DIR_H_MASK  ? 0 : 2];
	coords[1] = pixels[direction & GOD_ANCHOR_DIR_V_MASK  ? 1 : 3];
	coords[2] = pixels[direction & GOD_ANCHOR_DIR_H_MASK  ? 2 : 0];
	coords[3] = pixels[direction & GOD_ANCHOR_DIR_V_MASK  ? 3 : 1];
}
