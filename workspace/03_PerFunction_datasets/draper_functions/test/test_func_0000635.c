load_config (FileteaNode *self, GKeyFile *config)
{
  gchar *jquery_dir;


  self->priv->source_id_start_depth =
    g_key_file_get_integer (config,
                            "node",
                            "source-id-start-depth",
                            NULL);
  if (self->priv->source_id_start_depth == 0)
    self->priv->source_id_start_depth = DEFAULT_SOURCE_ID_START_DEPTH;
  else
    self->priv->source_id_start_depth =
      MIN (self->priv->source_id_start_depth, 16 + strlen (self->priv->id));


  set_max_node_bandwidth (self,
                          g_key_file_get_double (config,
                                                 "node",
                                                 "max-bandwidth-in",
                                                 NULL),
                          g_key_file_get_double (config,
                                                 "node",
                                                 "max-bandwidth-out",
                                                 NULL));


  self->priv->force_https = g_key_file_get_boolean (config,
                                                    "http",
                                                    "force-https",
                                                    NULL) == TRUE;
  if (self->priv->force_https)
    {
      self->priv->https_port = g_key_file_get_integer (config,
                                                       "https",
                                                       "port",
                                                       NULL);
    }


  self->priv->log_filename = g_key_file_get_string (config,
                                                    "log",
                                                    "http-log-file",
                                                    NULL);
  if (self->priv->log_filename != NULL && self->priv->log_filename[0] != '\0')
    setup_web_dir_logging (self);


  jquery_dir = g_key_file_get_string (config,
                                      "node",
                                      "jquery-dir",
                                      NULL);
  if (jquery_dir == NULL || jquery_dir[0] == '\0')
    jquery_dir = g_strdup (DEFAULT_JQUERY_DIR);

  evd_web_dir_set_root (self->priv->jquery_webdir, jquery_dir);
  g_free (jquery_dir);
}
