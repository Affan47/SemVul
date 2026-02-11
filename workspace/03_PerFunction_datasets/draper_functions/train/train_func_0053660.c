unity_webapps_service_get_context_daemon_argv (const gchar *name,
					       const gchar *domain,
					       const gchar *icon_url,
					       const gchar *mime_types)
{
  gchar **argv;
  const gchar *execdir;
  const gchar *preinstalled_desktop;

  execdir = g_getenv("UNITY_WEBAPPS_DAEMON_EXEC_DIR");

  if (execdir == NULL)
    {
      execdir = PACKAGE_LIBEXEC_DIR;
    }

  preinstalled_desktop = unity_webapps_service_get_preinstalled_app_desktop_id (name, domain);

  if (preinstalled_desktop == NULL)
    {
      argv = g_malloc (6 * sizeof (gchar *));
    }
  else
    {
      argv = g_malloc (7 * sizeof (gchar *));
    }

  argv[0] = g_strdup_printf("%s/unity-webapps-context-daemon", execdir);
  argv[1] = g_strdup (name);
  argv[2] = g_strdup (domain);
  argv[3] = icon_url ? g_strdup (icon_url) : g_strdup ("none");
  argv[4] = mime_types ? g_strdup (mime_types) : g_strdup("none");
  if (preinstalled_desktop == NULL)
    {
      argv[5] = NULL;
    }
  else
    {
      argv[5] = g_strdup (preinstalled_desktop);
      argv[6] = NULL;
    }

  return argv;
}
