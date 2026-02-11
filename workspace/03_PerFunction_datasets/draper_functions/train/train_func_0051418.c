monitor_credentials_cache (GoaKerberosIdentityManager  *self,
                           GError                     **error)
{
  krb5_ccache default_cache;
  const char *cache_type;
  const char *cache_path;
  GFileMonitor *monitor = NULL;
  krb5_error_code error_code;
  GError *monitoring_error = NULL;
  gboolean can_monitor = TRUE;

  error_code = krb5_cc_default (self->priv->kerberos_context, &default_cache);

  if (error_code != 0)
    {
      const char *error_message;
      error_message =
        krb5_get_error_message (self->priv->kerberos_context, error_code);

      g_set_error_literal (error,
                           GOA_IDENTITY_MANAGER_ERROR,
                           GOA_IDENTITY_MANAGER_ERROR_ACCESSING_CREDENTIALS,
                           error_message);
      krb5_free_error_message (self->priv->kerberos_context, error_message);

      return FALSE;
    }

  cache_type = krb5_cc_get_type (self->priv->kerberos_context, default_cache);
  g_assert (cache_type != NULL);

  if (strcmp (cache_type, "FILE") != 0 && strcmp (cache_type, "DIR") != 0)
    {
      goa_warning ("GoaKerberosIdentityManager: Using polling for change notification for credential cache type '%s'",
                   cache_type);
      can_monitor = FALSE;
    }

  g_free (self->priv->credentials_cache_type);
  self->priv->credentials_cache_type = g_strdup (cache_type);


  cache_path = krb5_cc_get_name (self->priv->kerberos_context, default_cache);


  if (cache_path[0] == ':')
    cache_path++;

  if (can_monitor)
    {
      GFile *file;

      file = g_file_new_for_path (cache_path);

      monitoring_error = NULL;
      if (strcmp (cache_type, "FILE") == 0)
        {
          monitor = g_file_monitor_file (file,
                                         G_FILE_MONITOR_NONE,
                                         NULL,
                                         &monitoring_error);
        }
      else if (strcmp (cache_type, "DIR") == 0)
        {
          GFile *directory;

          directory = g_file_get_parent (file);
          monitor = g_file_monitor_directory (directory,
                                              G_FILE_MONITOR_NONE,
                                              NULL,
                                              &monitoring_error);
          g_object_unref (directory);

        }
      g_object_unref (file);
    }

  if (monitor == NULL)
    {
      if (monitoring_error != NULL)
        {
          goa_warning ("GoaKerberosIdentityManager: Could not monitor credentials for %s (type %s), reverting to polling: %s",
                       cache_path,
                       cache_type,
                       monitoring_error != NULL? monitoring_error->message : "");
          g_clear_error (&monitoring_error);
        }
      can_monitor = FALSE;
    }
  else
    {
      self->priv->credentials_cache_changed_signal_id =
        g_signal_connect (G_OBJECT (monitor), "changed",
                          G_CALLBACK (on_credentials_cache_changed), self);
      self->priv->credentials_cache_monitor = monitor;
    }

  if (!can_monitor)
    self->priv->polling_timeout_id = g_timeout_add_seconds (FALLBACK_POLLING_INTERVAL, (GSourceFunc) on_polling_timeout, self);

  return TRUE;
}
