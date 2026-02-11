got_final_auth_result (SoupMessage *msg, gpointer data)
{
	SoupAuth *auth = data;

	g_signal_handlers_disconnect_by_func (msg, G_CALLBACK (got_final_auth_result), auth);

	if (auth != soup_message_get_auth (msg))
		return;

	if (msg->status_code != SOUP_STATUS_UNAUTHORIZED)
		SOUP_AUTH_NTLM_GET_PRIVATE (auth)->password_state = SOUP_NTLM_PASSWORD_ACCEPTED;
}
