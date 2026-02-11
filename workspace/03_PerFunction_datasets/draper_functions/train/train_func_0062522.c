cmd_objects_restore_location (SheetObject *so, gint location)
{
	gint loc = sheet_object_get_stacking (so);
	if (loc != location)
		sheet_object_adjust_stacking(so, location - loc);
}
