table_interface_get_row_extent_at (AtkTable *table,
                                   gint row,
                                   gint column)
{
	AtkGObjectAccessible *atk_gobj;
	GObject *g_obj;
	ECalendarItem *calitem;
	EaCalendarItem * ea_calitem = EA_CALENDAR_ITEM (table);

	atk_gobj = ATK_GOBJECT_ACCESSIBLE (ea_calitem);
	g_obj = atk_gobject_accessible_get_object (atk_gobj);
	if (!g_obj)
		return FALSE;

	calitem = E_CALENDAR_ITEM (g_obj);
	return calitem->cell_height;
}
