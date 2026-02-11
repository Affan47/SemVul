selection_not_empty_in_menu_callback (NautilusView *view, GList *selection)
{
	if (selection != NULL) {
		return TRUE;
	}


	if (!view->details->menu_states_untrustworthy) {
		g_warning ("Empty selection found when selection was expected. No action will be performed.");
	}

	return FALSE;
}
