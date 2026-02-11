load_new_location (NemoWindowSlot *slot,
		   GFile *location,
		   GList *selection,
		   gboolean tell_current_content_view,
		   gboolean tell_new_content_view)
{
	GList *selection_copy;
	NemoView *view;

	g_assert (slot != NULL);
	g_assert (location != NULL);

	selection_copy = eel_g_object_list_copy (selection);
	view = NULL;


        if (slot->content_view != NULL && tell_current_content_view) {
		view = slot->content_view;
		nemo_view_load_location (slot->content_view, location);
        }

        if (slot->new_content_view != NULL && tell_new_content_view &&
	    (!tell_current_content_view ||
	     slot->new_content_view != slot->content_view) ) {
		view = slot->new_content_view;
		nemo_view_load_location (slot->new_content_view, location);
        }
	if (view != NULL) {


		nemo_view_set_selection (view, selection_copy);
	}

	g_list_free_full (selection_copy, g_object_unref);
}
