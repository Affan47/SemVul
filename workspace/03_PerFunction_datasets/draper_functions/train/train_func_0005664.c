infd_session_proxy_user_notify_status_cb(InfUser* user,
                                         const GParamSpec* pspec,
                                         gpointer user_data)
{
  InfdSessionProxy* proxy;
  InfdSessionProxyPrivate* priv;
  InfdSessionProxySubscription* subscr;

  if(inf_user_get_status(user) == INF_USER_UNAVAILABLE)
  {
    proxy = INFD_SESSION_PROXY(user_data);
    priv = INFD_SESSION_PROXY_PRIVATE(proxy);

    if(inf_user_get_connection(user))
    {
      subscr = infd_session_proxy_find_subscription(
        proxy,
        inf_user_get_connection(user)
      );

      g_assert(subscr != NULL);
      subscr->users = g_slist_remove(subscr->users, user);

      g_object_set(G_OBJECT(user), "connection", NULL, NULL);
    }
    else
    {
      priv->local_users = g_slist_remove(priv->local_users, user);
    }

    inf_signal_handlers_disconnect_by_func(
      G_OBJECT(user),
      G_CALLBACK(infd_session_proxy_user_notify_status_cb),
      proxy
    );
  }
}
