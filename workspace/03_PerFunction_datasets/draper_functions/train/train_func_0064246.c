gdm_session_handle_secret_info_query (GdmDBusWorkerManager  *worker_manager_interface,
                                      GDBusMethodInvocation *invocation,
                                      const char            *service_name,
                                      const char            *query,
                                      GdmSession            *self)
{
        GdmSessionConversation *conversation;

        g_return_val_if_fail (self->priv->user_verifier_interface != NULL, FALSE);

        conversation = find_conversation_by_name (self, service_name);
        if (conversation != NULL) {
                set_pending_query (conversation, invocation);

                gdm_dbus_user_verifier_emit_secret_info_query (self->priv->user_verifier_interface,
                                                               service_name,
                                                               query);
        }

        return TRUE;
}
