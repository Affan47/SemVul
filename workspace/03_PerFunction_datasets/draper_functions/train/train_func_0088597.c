brasero_app_indicator_set_action (BraseroAppIndicator *indicator,
				  BraseroBurnAction action,
				  const gchar *string)
{
	indicator->priv->action = action;
	if (indicator->priv->action_string)
		g_free (indicator->priv->action_string);

	if (string)
		indicator->priv->action_string = g_strdup (string);
	else
		indicator->priv->action_string = NULL;

	brasero_app_indicator_set_progress_menu_text (indicator, -1);
}
