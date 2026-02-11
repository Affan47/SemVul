gedit_file_browser_widget_history_forward (GeditFileBrowserWidget *obj)
{
	if (obj->priv->locations)
	{
		jump_to_location (obj, obj->priv->current_location->prev,
				  FALSE);
	}
}
