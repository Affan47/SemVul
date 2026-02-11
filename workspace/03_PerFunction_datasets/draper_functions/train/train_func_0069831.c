add_submenu (GtkUIManager *ui_manager,
	     GtkActionGroup *action_group,
	     guint merge_id,
	     const char *parent_path,
	     const char *uri,
	     const char *label,
	     GdkPixbuf *pixbuf,
	     gboolean add_action)
{
	char *escaped_label;
	char *action_name;
	char *submenu_name;
	char *escaped_submenu_name;
	GtkAction *action;

	if (parent_path != NULL) {
		action_name = nautilus_escape_action_name (uri, "submenu_");
		submenu_name = g_path_get_basename (uri);
		escaped_submenu_name = escape_action_path (submenu_name);
		escaped_label = eel_str_double_underscores (label);

		if (add_action) {
			action = gtk_action_new (action_name,
						 escaped_label,
						 NULL,
						 NULL);
			if (pixbuf != NULL) {
				gtk_action_set_gicon (action, G_ICON (pixbuf));
			}

			g_object_set (action, "hide-if-empty", FALSE, NULL);

			gtk_action_group_add_action (action_group,
						     action);
			g_object_unref (action);
		}

		gtk_ui_manager_add_ui (ui_manager,
				       merge_id,
				       parent_path,
				       escaped_submenu_name,
				       action_name,
				       GTK_UI_MANAGER_MENU,
				       FALSE);
		g_free (action_name);
		g_free (escaped_label);
		g_free (submenu_name);
		g_free (escaped_submenu_name);
	}
}
