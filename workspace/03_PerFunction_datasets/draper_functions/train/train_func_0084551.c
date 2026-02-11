gl_ui_util_set_verb_sensitive (GtkUIManager  *ui,
			       gchar         *cname,
			       gboolean       sensitive)
{
	GtkAction *action;

	gl_debug (DEBUG_UI, "START");

	g_return_if_fail (cname != NULL);
	g_return_if_fail (GTK_IS_UI_MANAGER (ui));

	action = gtk_ui_manager_get_action (ui, cname);

	if (action) {
		gl_debug (DEBUG_UI, "Set action \"%s\" sensitive = %d", cname, sensitive);
		gtk_action_set_sensitive (action, sensitive);
	}

	gl_debug (DEBUG_UI, "END");
}
