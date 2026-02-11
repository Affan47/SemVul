glade_project_verify_adaptor (GladeProject       *project,
			      GladeWidgetAdaptor *adaptor,
			      const gchar        *path_name,
			      GString            *string,
			      gboolean            saving,
			      gboolean            forwidget,
			      GladeSupportMask   *mask)
{
	GladeSupportMask    support_mask = GLADE_SUPPORT_OK;
	GladeWidgetAdaptor *adaptor_iter;
	gint                target_major, target_minor;
	gchar              *catalog = NULL;

	for (adaptor_iter = adaptor; adaptor_iter && support_mask == GLADE_SUPPORT_OK;
	     adaptor_iter = glade_widget_adaptor_get_parent_adaptor (adaptor_iter))
	{

		g_object_get (adaptor_iter, "catalog", &catalog, NULL);
		glade_project_target_version_for_adaptor (project, adaptor_iter,
							  &target_major,
							  &target_minor);


		if (!GWA_VERSION_CHECK (adaptor_iter, target_major, target_minor))
		{
			if (forwidget)
				g_string_append_printf (string,
							WIDGET_VERSION_CONFLICT_MSGFMT,
							catalog,
							GWA_VERSION_SINCE_MAJOR (adaptor_iter),
							GWA_VERSION_SINCE_MINOR (adaptor_iter),
							catalog, target_major, target_minor);
			else
				g_string_append_printf (string,
							WIDGET_VERSION_CONFLICT_FMT,
							path_name, adaptor_iter->title, catalog,
							GWA_VERSION_SINCE_MAJOR (adaptor_iter),
							GWA_VERSION_SINCE_MINOR (adaptor_iter));

			support_mask |= GLADE_SUPPORT_MISMATCH;
		}
		else if (project->priv->format == GLADE_PROJECT_FORMAT_GTKBUILDER &&
			 (target_major < GWA_BUILDER_SINCE_MAJOR (adaptor_iter) ||
			  (target_major == GWA_BUILDER_SINCE_MAJOR (adaptor_iter) &&
			   target_minor < GWA_BUILDER_SINCE_MINOR (adaptor_iter))))
		{
			if (forwidget)
				g_string_append_printf (string,
							WIDGET_BUILDER_VERSION_CONFLICT_MSGFMT,
							catalog,
							GWA_BUILDER_SINCE_MAJOR (adaptor_iter),
							GWA_BUILDER_SINCE_MINOR (adaptor_iter),
							catalog, target_major, target_minor);
			else
				g_string_append_printf (string,
							WIDGET_BUILDER_VERSION_CONFLICT_FMT,
							path_name, adaptor_iter->title, catalog,
							GWA_BUILDER_SINCE_MAJOR (adaptor_iter),
							GWA_BUILDER_SINCE_MINOR (adaptor_iter));

			support_mask |= GLADE_SUPPORT_MISMATCH;
		}


		if (project->priv->format == GLADE_PROJECT_FORMAT_GTKBUILDER &&
		    GWA_LIBGLADE_ONLY (adaptor_iter))
		{
			if (forwidget)
			{
				if (string->len)
					g_string_append (string, "\n");
				g_string_append_printf (string, WIDGET_LIBGLADE_ONLY_MSG);
			}
			else
				g_string_append_printf (string,
							WIDGET_LIBGLADE_ONLY_FMT,
							path_name, adaptor_iter->title, catalog,
							target_major, target_minor);

			support_mask |= GLADE_SUPPORT_LIBGLADE_ONLY;
		}
		else if (project->priv->format == GLADE_PROJECT_FORMAT_LIBGLADE &&
			 GWA_LIBGLADE_UNSUPPORTED (adaptor_iter))
		{
			if (forwidget)
			{
				if (string->len)
					g_string_append (string, "\n");

				g_string_append_printf (string, WIDGET_LIBGLADE_UNSUPPORTED_MSG);
			}
			else
				g_string_append_printf (string, WIDGET_LIBGLADE_UNSUPPORTED_FMT,
							path_name, adaptor_iter->title, catalog,
							target_major, target_minor);

			support_mask |= GLADE_SUPPORT_LIBGLADE_UNSUPPORTED;
		}

		if (!saving && GWA_DEPRECATED (adaptor_iter))
		{
			if (forwidget)
			{
				if (string->len)
					g_string_append (string, "\n");

				g_string_append_printf (string, WIDGET_DEPRECATED_MSG);
			}
			else
				g_string_append_printf (string, WIDGET_DEPRECATED_FMT,
							path_name, adaptor_iter->title, catalog,
							target_major, target_minor);

			support_mask |= GLADE_SUPPORT_DEPRECATED;
		}
		g_free (catalog);
	}
	if (mask)
		*mask = support_mask;

}
