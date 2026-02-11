gusb_cmd_run (GUsbCmdPrivate *priv, const gchar *command, gchar **values, GError **error)
{
	gboolean ret = FALSE;
	guint i;
	GUsbCmdItem *item;
	GString *string;


	for (i=0; i<priv->cmd_array->len; i++) {
		item = g_ptr_array_index (priv->cmd_array, i);
		if (g_strcmp0 (item->name, command) == 0) {
			ret = item->callback (priv, values, error);
			goto out;
		}
	}


	string = g_string_new ("");

	g_string_append_printf (string, "%s\n", "Command not found, valid commands are:");
	for (i=0; i<priv->cmd_array->len; i++) {
		item = g_ptr_array_index (priv->cmd_array, i);
		g_string_append_printf (string, " * %s\n", item->name);
	}
	g_set_error_literal (error, 1, 0, string->str);
	g_string_free (string, TRUE);
out:
	return ret;
}
