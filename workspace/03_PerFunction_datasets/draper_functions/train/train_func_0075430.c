e2_filelist_disable_one_refresh (E2_ListChoice pane)
{
	if (_e2_filelist_check_active_pane (pane))
	{
		refresh_active_refcount++;
		if (refresh_active_refcount == 1)
		{
			LISTS_LOCK
			curr_view->listcontrols.norefresh = TRUE;
			LISTS_UNLOCK
		}
	}
	else
	{
		refresh_inactive_refcount++;
		if (refresh_inactive_refcount == 1)
		{
			LISTS_LOCK
			other_view->listcontrols.norefresh = TRUE;
			LISTS_UNLOCK
		}
	}
}
