glade_project_verify_signal_internal (GladeWidget *widget,
                                      GladeSignal *signal,
                                      const gchar *path_name,
                                      GString *string,
                                      gboolean forwidget,
				      GladeVerifyFlags flags)
{
  GladeSignalClass   *signal_class;
  GladeWidgetAdaptor *adaptor;
  gint                target_major, target_minor;
  gchar              *catalog;
  GladeProject       *project;

  signal_class =
      glade_widget_adaptor_get_signal_class (glade_widget_get_adaptor (widget),
                                             glade_signal_get_name (signal));

  if (!signal_class)
    return;

  adaptor = glade_signal_class_get_adaptor (signal_class);
  project = glade_widget_get_project (widget);

  if (!project)
    return;

  g_object_get (adaptor, "catalog", &catalog, NULL);
  glade_project_target_version_for_adaptor (project, adaptor,
                                            &target_major, &target_minor);

  if ((flags & GLADE_VERIFY_VERSIONS) != 0 &&
      !GSC_VERSION_CHECK (signal_class, target_major, target_minor))
    {
      GLADE_NOTE (VERIFY, g_print ("VERIFY: Signal '%s' of adaptor %s not avalable in version %d.%d\n",
				   glade_signal_get_name (signal),
				   glade_widget_adaptor_get_name (adaptor),
				   target_major, target_minor));

      if (forwidget)
        {
          gchar *warning;

          warning = g_strdup_printf (SIGNAL_VERSION_CONFLICT_MSGFMT,
                                     catalog,
                                     glade_signal_class_since_major (signal_class),
                                     glade_signal_class_since_minor (signal_class),
                                     catalog, target_major, target_minor);
          glade_signal_set_support_warning (signal, warning);
          g_free (warning);
        }
      else
        g_string_append_printf (string,
                                SIGNAL_VERSION_CONFLICT_FMT,
                                path_name,
                                glade_signal_get_name (signal),
                                glade_widget_adaptor_get_title (adaptor),
                                catalog,
                                glade_signal_class_since_major (signal_class),
                                glade_signal_class_since_minor (signal_class));
    }
  else if ((flags & GLADE_VERIFY_DEPRECATIONS) != 0 &&
	   glade_signal_class_deprecated (signal_class))
    {
      GLADE_NOTE (VERIFY, g_print ("VERIFY: Signal '%s' of adaptor %s is deprecated\n",
				   glade_signal_get_name (signal),
				   glade_widget_adaptor_get_name (adaptor)));

      if (forwidget)
	glade_signal_set_support_warning (signal, SIGNAL_DEPRECATED_MSG);
      else
        g_string_append_printf (string,
                                SIGNAL_DEPRECATED_FMT,
                                path_name,
                                glade_signal_get_name (signal),
                                glade_widget_adaptor_get_title (adaptor));
    }
  else if (forwidget)
    glade_signal_set_support_warning (signal, NULL);

  g_free (catalog);
}
