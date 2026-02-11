smtp_auth_login_user_recv(SMTPSession *session, const gchar *msg)
{
	gchar buf[MESSAGEBUFSIZE];

	session->state = SMTP_AUTH_LOGIN_PASS;

	if (!strncmp(msg, "334 ", 4))
		base64_encode(buf, session->pass, strlen(session->pass));
	else

		g_snprintf(buf, sizeof(buf), "*");

	if (session_send_msg(SESSION(session), SESSION_MSG_NORMAL, buf) < 0)
		return SM_ERROR;

	log_print(LOG_PROTOCOL, "ESMTP> [PASSWORD]\n");

	return SM_OK;
}
