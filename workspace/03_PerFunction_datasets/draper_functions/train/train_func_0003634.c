gdm_session_send_environment (GdmSession *self,
                              const char *service_name)
{
        GdmSessionConversation *conversation;

        g_return_if_fail (GDM_IS_SESSION (self));

        conversation = find_conversation_by_name (self, service_name);
        if (conversation != NULL) {
                send_environment (self, conversation);
        }
}
