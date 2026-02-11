ui_delete(char *cmd)
{
	char            cookies_str[ISAKMP_HDR_COOKIES_LEN * 2 + 1];
	char            message_id_str[ISAKMP_HDR_MESSAGE_ID_LEN * 2 + 1];
	u_int8_t        cookies[ISAKMP_HDR_COOKIES_LEN];
	u_int8_t        message_id_buf[ISAKMP_HDR_MESSAGE_ID_LEN];
	u_int8_t       *message_id = message_id_buf;
	struct sa      *sa;

	if (sscanf(cmd, "d %32s %8s", cookies_str, message_id_str) != 2) {
		log_print("ui_delete: command \"%s\" malformed", cmd);
		return;
	}
	if (strcmp(message_id_str, "-") == 0)
		message_id = 0;

	if (hex2raw(cookies_str, cookies, ISAKMP_HDR_COOKIES_LEN) == -1 ||
	    (message_id && hex2raw(message_id_str, message_id_buf,
	    ISAKMP_HDR_MESSAGE_ID_LEN) == -1)) {
		log_print("ui_delete: command \"%s\" has bad arguments", cmd);
		return;
	}
	sa = sa_lookup(cookies, message_id);
	if (!sa) {
		log_print("ui_delete: command \"%s\" found no SA", cmd);
		return;
	}
	LOG_DBG((LOG_UI, 20,
	    "ui_delete: deleting SA for cookie \"%s\" msgid \"%s\"",
	    cookies_str, message_id_str));
	sa_delete(sa, 1);
}
