item_cursor_unrealize (GocItem *item)
{
	GnmItemCursor *ic = GNM_ITEM_CURSOR (item);

	if (ic->animation_timer != 0) {
		g_source_remove (ic->animation_timer);
		ic->animation_timer = 0;
	}

	parent_class->unrealize (item);
}
