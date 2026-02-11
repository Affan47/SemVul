scripts_added_or_changed_callback (NemoDirectory *directory,
				   GList *files,
				   gpointer callback_data)
{
	NemoView *view;

	view = NEMO_VIEW (callback_data);

	view->details->scripts_invalid = TRUE;
	if (view->details->active) {
		schedule_update_menus (view);
	}
}
