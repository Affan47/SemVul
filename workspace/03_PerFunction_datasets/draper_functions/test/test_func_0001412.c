daemon_local_check_auth (Daemon                *daemon,
                         User                  *user,
                         const gchar           *action_id,
                         gboolean               allow_interaction,
                         AuthorizedCallback     authorized_cb,
                         GDBusMethodInvocation *context,
                         gpointer               authorized_cb_data,
                         GDestroyNotify         destroy_notify)
{
        CheckAuthData *data;
        PolkitSubject *subject;
        PolkitCheckAuthorizationFlags flags;

        data = g_new0 (CheckAuthData, 1);
        data->daemon = g_object_ref (daemon);
        if (user)
                data->user = g_object_ref (user);
        data->context = context;
        data->authorized_cb = authorized_cb;
        data->data = authorized_cb_data;
        data->destroy_notify = destroy_notify;

        subject = polkit_system_bus_name_new (g_dbus_method_invocation_get_sender (context));

        flags = POLKIT_CHECK_AUTHORIZATION_FLAGS_NONE;
        if (allow_interaction)
                flags |= POLKIT_CHECK_AUTHORIZATION_FLAGS_ALLOW_USER_INTERACTION;
        polkit_authority_check_authorization (daemon->priv->authority,
                                              subject,
                                              action_id,
                                              NULL,
                                              flags,
                                              NULL,
                                              (GAsyncReadyCallback) check_auth_cb,
                                              data);

        g_object_unref (subject);
}
