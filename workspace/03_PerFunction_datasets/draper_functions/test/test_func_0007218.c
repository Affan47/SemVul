nemo_window_back_or_forward (NemoWindow *window,
				 gboolean back,
				 guint distance,
				 gboolean new_tab)
{
	NemoWindowSlot *slot;
	GList *list;
	GFile *location;
        guint len;
        NemoBookmark *bookmark;
	GFile *old_location;

	slot = nemo_window_get_active_slot (window);
	list = back ? slot->back_list : slot->forward_list;

        len = (guint) g_list_length (list);


        if (len == 0)
                return;


        if (distance >= len)
                distance = len - 1;

        bookmark = g_list_nth_data (list, distance);
	location = nemo_bookmark_get_location (bookmark);

	if (new_tab) {
		nemo_window_slot_open_location_full (slot, location,
							 NEMO_WINDOW_OPEN_FLAG_NEW_TAB,
							 NULL, NULL, NULL);
	} else {
		char *scroll_pos;

		old_location = nemo_window_slot_get_location (slot);
		scroll_pos = nemo_bookmark_get_scroll_pos (bookmark);
		begin_location_change
			(slot,
			 location, old_location, NULL,
			 back ? NEMO_LOCATION_CHANGE_BACK : NEMO_LOCATION_CHANGE_FORWARD,
			 distance,
			 scroll_pos,
			 NULL, NULL);

		g_clear_object (&old_location);
		g_free (scroll_pos);
	}

	g_object_unref (location);
}
