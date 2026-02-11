analyze_tab_state (GeditTab    *tab,
		   GeditWindow *window)
{
	GeditTabState ts;

	ts = gedit_tab_get_state (tab);

	switch (ts)
	{
		case GEDIT_TAB_STATE_LOADING:
		case GEDIT_TAB_STATE_REVERTING:
			window->priv->state |= GEDIT_WINDOW_STATE_LOADING;
			break;

		case GEDIT_TAB_STATE_SAVING:
			window->priv->state |= GEDIT_WINDOW_STATE_SAVING;
			break;

		case GEDIT_TAB_STATE_PRINTING:
		case GEDIT_TAB_STATE_PRINT_PREVIEWING:
			window->priv->state |= GEDIT_WINDOW_STATE_PRINTING;
			break;

		case GEDIT_TAB_STATE_LOADING_ERROR:
		case GEDIT_TAB_STATE_REVERTING_ERROR:
		case GEDIT_TAB_STATE_SAVING_ERROR:
		case GEDIT_TAB_STATE_GENERIC_ERROR:
			window->priv->state |= GEDIT_WINDOW_STATE_ERROR;
			++window->priv->num_tabs_with_error;
		default:

			break;
	}
}
