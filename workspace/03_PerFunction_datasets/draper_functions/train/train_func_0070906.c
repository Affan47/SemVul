unity_webapps_notification_context_new (UnityWebappsContext *main_context, GError **error)
{
  UnityWebappsNotificationContext *context;

  context = g_malloc0 (sizeof (UnityWebappsNotificationContext));
  context->notification_rate = 0;

  context->notification_proxy =
    unity_webapps_gen_notification_proxy_new_sync (unity_webapps_service_get_connection (main_context->priv->service) ,
						   G_DBUS_PROXY_FLAGS_NONE,
						   main_context->priv->context_name,
						   UNITY_WEBAPPS_NOTIFICATION_PATH,
						   NULL ,
						   error);

  if (error && (*error != NULL))
    {
      g_critical ("Error creating notification context proxy object for %s: %s", main_context->priv->context_name, (*error)->message);

      return NULL;
    }

  return context;
}
