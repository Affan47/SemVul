schedule_update_menus (NautilusView *view)
{
	g_assert (NAUTILUS_IS_VIEW (view));


	if (view->details->slot == NULL ||
	    !view->details->active) {
		return;
	}

	view->details->menu_states_untrustworthy = TRUE;


	if (view->details->update_menus_timeout_id == 0) {
		view->details->update_menus_timeout_id
			= g_timeout_add (view->details->update_interval, update_menus_timeout_callback, view);
	}
}
