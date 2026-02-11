egg_sm_client_get_state_file (EggSMClient *client)
{
  EggSMClientPrivate *priv = EGG_SM_CLIENT_GET_PRIVATE (client);
  char *state_file_path;
  GError *err = NULL;

  g_return_val_if_fail (client == global_client, NULL);

  if (!sm_client_state_file)
    return NULL;
  if (priv->state_file)
    return priv->state_file;

  if (!strncmp (sm_client_state_file, "file://", 7))
    state_file_path = g_filename_from_uri (sm_client_state_file, NULL, NULL);
  else
    state_file_path = g_strdup (sm_client_state_file);

  priv->state_file = g_key_file_new ();
  if (!g_key_file_load_from_file (priv->state_file, state_file_path, 0, &err))
    {
      g_warning ("Could not load SM state file '%s': %s",
		 sm_client_state_file, err->message);
      g_clear_error (&err);
      g_key_file_free (priv->state_file);
      priv->state_file = NULL;
    }

  g_free (state_file_path);
  return priv->state_file;
}
