glade_project_verify_signal (GladeWidget  *widget,
			     GladeSignal  *signal,
			     const gchar  *path_name,
			     GString      *string,
			     gboolean      forwidget)
{
	GladeSignalClass *signal_class;
	gint target_major, target_minor;
	gchar *catalog;

	signal_class =
		glade_widget_adaptor_get_signal_class (widget->adaptor,
						       signal->name);

	if (!signal_class)
		return;
	g_assert (signal_class->adaptor);

	g_object_get (signal_class->adaptor, "catalog", &catalog, NULL);
	glade_project_target_version_for_adaptor (widget->project,
						  signal_class->adaptor,
						  &target_major,
						  &target_minor);

	if (!GSC_VERSION_CHECK (signal_class, target_major, target_minor))
	{
		if (forwidget)
		{
			gchar *warning;

			warning = g_strdup_printf (SIGNAL_VERSION_CONFLICT_MSGFMT,
						   catalog,
						   signal_class->version_since_major,
						   signal_class->version_since_minor,
						   catalog, target_major, target_minor);
			glade_signal_set_support_warning (signal, warning);
			g_free (warning);
		}
		else
			g_string_append_printf (string,
						SIGNAL_VERSION_CONFLICT_FMT,
						path_name,
						signal->name,
						signal_class->adaptor->title,
						catalog,
						signal_class->version_since_major,
						signal_class->version_since_minor);
	}
	else if (forwidget)
		glade_signal_set_support_warning (signal, NULL);

	g_free (catalog);
}
