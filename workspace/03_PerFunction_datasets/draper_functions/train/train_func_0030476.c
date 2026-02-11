g_proxy_volume_monitor_register (GIOModule *module)
{
  GDir *dir;
  GError *error;
  const char *monitors_dir;


  g_proxy_volume_monitor_register_type (G_TYPE_MODULE (module));


  monitors_dir = g_getenv ("GVFS_MONITOR_DIR");
  if (monitors_dir == NULL || *monitors_dir == 0)
    monitors_dir = REMOTE_VOLUME_MONITORS_DIR;

  error = NULL;
  dir = g_dir_open (monitors_dir, 0, &error);
  if (dir == NULL)
    {
      g_warning ("cannot open directory %s: %s", monitors_dir, error->message);
      g_error_free (error);
    }
  else
    {
      const char *name;

      while ((name = g_dir_read_name (dir)) != NULL)
        {
          GKeyFile *key_file;
          char *type_name;
          char *path;
          char *dbus_name;
          gboolean is_native;
          int native_priority;

          type_name = NULL;
          key_file = NULL;
          dbus_name = NULL;
          path = NULL;

          if (!g_str_has_suffix (name, ".monitor"))
            goto cont;

          path = g_build_filename (monitors_dir, name, NULL);

          key_file = g_key_file_new ();
          error = NULL;
          if (!g_key_file_load_from_file (key_file, path, G_KEY_FILE_NONE, &error))
            {
              g_warning ("error loading key-value file %s: %s", path, error->message);
              g_error_free (error);
              goto cont;
            }

          type_name = g_key_file_get_string (key_file, "RemoteVolumeMonitor", "Name", &error);
          if (error != NULL)
            {
              g_warning ("error extracting Name key from %s: %s", path, error->message);
              g_error_free (error);
              goto cont;
            }

          dbus_name = g_key_file_get_string (key_file, "RemoteVolumeMonitor", "DBusName", &error);
          if (error != NULL)
            {
              g_warning ("error extracting DBusName key from %s: %s", path, error->message);
              g_error_free (error);
              goto cont;
            }

          is_native = g_key_file_get_boolean (key_file, "RemoteVolumeMonitor", "IsNative", &error);
          if (error != NULL)
            {
              g_warning ("error extracting IsNative key from %s: %s", path, error->message);
              g_error_free (error);
              goto cont;
            }

          if (is_native)
            {
              native_priority = g_key_file_get_integer (key_file, "RemoteVolumeMonitor", "NativePriority", &error);
              if (error != NULL)
                {
                  g_warning ("error extracting NativePriority key from %s: %s", path, error->message);
                  g_error_free (error);
                  goto cont;
                }
            }
          else
            {
              native_priority = 0;
            }

          register_volume_monitor (G_TYPE_MODULE (module),
                                   type_name,
                                   dbus_name,
                                   is_native,
                                   native_priority);

        cont:

          g_free (type_name);
          g_free (dbus_name);
          g_free (path);
          if (key_file != NULL)
              g_key_file_free (key_file);
        }
      g_dir_close (dir);
    }
}
