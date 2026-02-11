totem_disc_recorder_file_opened (TotemObject *totem,
				 const char *mrl,
				 TotemDiscRecorderPlugin *pi)
{
	TotemDiscRecorderPluginPrivate *priv = pi->priv;
	GtkAction *action;


	if (g_str_has_prefix (mrl, "file:")) {


		action = gtk_action_group_get_action (priv->action_group, "VideoBurnToDisc");
		gtk_action_set_visible (action, TRUE);
		action = gtk_action_group_get_action (priv->action_group, "VideoDVDCopy");
		gtk_action_set_visible (action, FALSE);
		action = gtk_action_group_get_action (priv->action_group, "VideoVCDCopy");
		gtk_action_set_visible (action, FALSE);
	}
	else if (g_str_has_prefix (mrl, "dvd:")) {
		action = gtk_action_group_get_action (priv->action_group, "VideoBurnToDisc");
		gtk_action_set_visible (action, FALSE);
		action = gtk_action_group_get_action (priv->action_group, "VideoDVDCopy");
		gtk_action_set_visible (action, TRUE);
		action = gtk_action_group_get_action (priv->action_group, "VideoVCDCopy");
		gtk_action_set_visible (action, FALSE);
	}
	else if (g_str_has_prefix (mrl, "vcd:")) {
		action = gtk_action_group_get_action (priv->action_group, "VideoBurnToDisc");
		gtk_action_set_visible (action, FALSE);
		action = gtk_action_group_get_action (priv->action_group, "VideoDVDCopy");
		gtk_action_set_visible (action, FALSE);
		action = gtk_action_group_get_action (priv->action_group, "VideoVCDCopy");
		gtk_action_set_visible (action, TRUE);
	}
	else {
		action = gtk_action_group_get_action (priv->action_group, "VideoBurnToDisc");
		gtk_action_set_visible (action, FALSE);
		action = gtk_action_group_get_action (priv->action_group, "VideoDVDCopy");
		gtk_action_set_visible (action, FALSE);
		action = gtk_action_group_get_action (priv->action_group, "VideoVCDCopy");
		gtk_action_set_visible (action, FALSE);
	}
}
