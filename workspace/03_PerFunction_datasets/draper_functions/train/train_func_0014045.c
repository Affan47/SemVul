unity_webapps_installer_install_application ()
{
  UnityWebappsApplicationInfo *info;
  gchar *saved_icon, *desktop_file_path;
  GError *error;

  info = unity_webapps_application_info_new (name, domain, icon_uri, NULL);

  printf("Installing application: %s at %s\n", name, domain);
  saved_icon = unity_webapps_application_info_save_icon_file (info);

  if (saved_icon == NULL)
	{
	  g_error ("Failed to save icon file!");
	  exit(1);
	}

  printf("   * Wrote icon file: %s", saved_icon);

  error = NULL;

  unity_webapps_application_info_ensure_desktop_file (info,
													 &error);

  if (error != NULL)
	{
	  g_error ("Failed to write desktop file: %s \n", error->message);
	  g_error_free (error);

	  exit (1);
	}

  desktop_file_path = unity_webapps_application_info_get_desktop_file_path (info);

  printf("   * Wrote desktop file: %s\n", desktop_file_path);

  if (homepage != NULL)
	{
	  homepage = domain;
	}

  unity_webapps_application_info_set_homepage (info, homepage);


  return;
}
