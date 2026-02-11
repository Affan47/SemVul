sheet_object_position_pts_get (SheetObject const *so, double *coords)
{
	g_return_if_fail (IS_SHEET_OBJECT (so));
	sheet_object_anchor_to_pts (&so->anchor, so->sheet, coords);
}
