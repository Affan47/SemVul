ay_conversation_buddy_arrive(Conversation *conv, const char *alias,
	const char *handle)
{
	char buf[1024];

	ay_conversation_fellows_append(conv, alias, handle);

        if (!strcmp(alias, handle))
		snprintf(buf, sizeof(buf), _("<b>%s has joined the chat.</b>"),
			handle);
	else
		snprintf(buf, sizeof(buf), _("<b>%s (%s) has joined the chat.</b>"),
			alias, handle);

	ay_conversation_display_notification(conv, buf,
		CHAT_NOTIFICATION_JOIN);
}
