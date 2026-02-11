ifile_savable_save (IAnjutaFileSavable* file, GError **e)
{
	AnjutaDesignDocument* self = ANJUTA_DESIGN_DOCUMENT(file);
	AnjutaDesignDocumentPrivate* priv = ADD_GET_PRIVATE(self);

	GladeProject* project = glade_design_view_get_project(GLADE_DESIGN_VIEW(self));

	if (glade_project_get_path(project) != NULL)
	{
		AnjutaStatus *status;

		status = anjuta_shell_get_status (ANJUTA_PLUGIN(priv->glade_plugin)->shell, NULL);

		if (glade_project_save (project, glade_project_get_path(project),
								NULL))
		{
			gchar *name;
			GFile *file;

			name = glade_project_get_name (project);
			anjuta_status_set (status, _("Glade project '%s' saved"), name);
			g_free (name);
			g_signal_emit_by_name(G_OBJECT(self), "update-save-ui", TRUE);

			file = g_file_new_for_path (glade_project_get_path(project));
			g_signal_emit_by_name(G_OBJECT(self), "saved", file);
			g_object_unref (file);
		}
		else
		{
			anjuta_util_dialog_warning (GTK_WINDOW (ANJUTA_PLUGIN(priv->glade_plugin)->shell),
										_("Invalid Glade file name"));
			g_signal_emit_by_name(G_OBJECT(self), "saved", NULL);
		}
		return;
	}
	DEBUG_PRINT("%s", "Invalid use of ifile_savable_save!");
}
