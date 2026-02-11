begin_verification_conversation (GdmSession            *self,
                                 GDBusMethodInvocation *invocation,
                                 const char            *service_name)
{
        GdmSessionConversation *conversation;

        gdm_session_start_conversation (self, service_name);

        conversation = find_conversation_by_name (self, service_name);

        if (conversation == NULL) {
                g_dbus_method_invocation_return_error (invocation,
                                                       G_DBUS_ERROR,
                                                       G_DBUS_ERROR_SPAWN_FAILED,
                                                       _("Could not create authentication helper process"));
        }

        return conversation;
}
