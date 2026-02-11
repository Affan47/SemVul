found_password_cb (GnomeKeyringResult  result,
                   GList              *list,
                   gpointer            user_data)
{
  SwService *service = SW_SERVICE (user_data);
  SwServiceLastfm *lastfm = SW_SERVICE_LASTFM (service);
  SwServiceLastfmPrivate *priv = lastfm->priv;

  g_free (priv->username);
  g_free (priv->password);
  g_free (priv->session_key);
  priv->session_key = NULL;
  priv->username = NULL;
  priv->password = NULL;
  priv->checked_with_server = FALSE;

  if (result == GNOME_KEYRING_RESULT_OK && list != NULL) {
    GnomeKeyringNetworkPasswordData *data = list->data;

    priv->username = g_strdup (data->user);
    priv->password = g_strdup (data->password);

    if (sw_is_online ()) {
      verify_user (service);
    }
  } else {
    if (result != GNOME_KEYRING_RESULT_NO_MATCH) {
      g_warning (G_STRLOC ": Error getting password: %s", gnome_keyring_result_to_message (result));
    }
  }

  sw_service_emit_user_changed (service);
  sw_service_emit_capabilities_changed (service, get_dynamic_caps (service));
}
