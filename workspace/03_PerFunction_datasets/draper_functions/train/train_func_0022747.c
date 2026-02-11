gedit_file_browser_message_set_root_get_property (GObject    *obj,
                                                  guint       prop_id,
                                                  GValue     *value,
                                                  GParamSpec *pspec)
{
	GeditFileBrowserMessageSetRoot *msg;

	msg = GEDIT_FILE_BROWSER_MESSAGE_SET_ROOT (obj);

	switch (prop_id)
	{
		case PROP_LOCATION:
			g_value_set_object (value, msg->priv->location);
			break;
		case PROP_VIRTUAL:
			g_value_set_string (value, msg->priv->virtual);
			break;
	}
}
