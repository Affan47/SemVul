goa_oauth_provider_build_object (GoaProvider         *provider,
                                 GoaObjectSkeleton   *object,
                                 GKeyFile            *key_file,
                                 const gchar         *group,
                                 GDBusConnection     *connection,
                                 gboolean             just_added,
                                 GError             **error)
{
  GoaOAuthBased *oauth_based;
  gchar *identity;

  identity = NULL;

  oauth_based = goa_object_get_oauth_based (GOA_OBJECT (object));
  if (oauth_based != NULL)
    goto out;

  oauth_based = goa_oauth_based_skeleton_new ();
  goa_oauth_based_set_consumer_key (oauth_based,
                                    goa_oauth_provider_get_consumer_key (GOA_OAUTH_PROVIDER (provider)));
  goa_oauth_based_set_consumer_secret (oauth_based,
                                       goa_oauth_provider_get_consumer_secret (GOA_OAUTH_PROVIDER (provider)));

  g_dbus_interface_skeleton_set_flags (G_DBUS_INTERFACE_SKELETON (oauth_based),
                                       G_DBUS_INTERFACE_SKELETON_FLAGS_HANDLE_METHOD_INVOCATIONS_IN_THREAD);
  goa_object_skeleton_set_oauth_based (object, oauth_based);
  g_signal_connect (oauth_based,
                    "handle-get-access-token",
                    G_CALLBACK (on_handle_get_access_token),
                    NULL);

 out:
  g_object_unref (oauth_based);
  g_free (identity);
  return TRUE;
}
