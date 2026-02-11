pop3_gen_send(Pop3Session *session, const gchar *format, ...)
{
	gchar buf[POPBUFSIZE + 1];
	va_list args;

	va_start(args, format);
	g_vsnprintf(buf, sizeof(buf) - 2, format, args);
	va_end(args);

	if (!g_ascii_strncasecmp(buf, "PASS ", 5))
		log_print(LOG_PROTOCOL, "POP3> PASS ********\n");
	else
		log_print(LOG_PROTOCOL, "POP3> %s\n", buf);

	session_send_msg(SESSION(session), SESSION_MSG_NORMAL, buf);
}
