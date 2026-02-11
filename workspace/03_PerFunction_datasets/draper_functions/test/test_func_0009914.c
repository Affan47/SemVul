alloc_event(const struct ast_security_event_common *sec)
{
	struct ast_str *str = ast_str_alloca(TIMESTAMP_STR_LEN);
	struct timeval tv = ast_tvnow();
	const char *severity_str;

	if (check_event_type(sec->event_type)) {
		return NULL;
	}

	encode_timestamp(&str, &tv);

	severity_str = S_OR(
		ast_security_event_severity_get_name(sec_events[sec->event_type].severity),
		"Unknown"
	);

	return ast_event_new(AST_EVENT_SECURITY,
		AST_EVENT_IE_SECURITY_EVENT, AST_EVENT_IE_PLTYPE_UINT, sec->event_type,
		AST_EVENT_IE_EVENT_VERSION, AST_EVENT_IE_PLTYPE_UINT, sec->version,
		AST_EVENT_IE_EVENT_TV, AST_EVENT_IE_PLTYPE_STR, ast_str_buffer(str),
		AST_EVENT_IE_SERVICE, AST_EVENT_IE_PLTYPE_STR, sec->service,
		AST_EVENT_IE_SEVERITY, AST_EVENT_IE_PLTYPE_STR, severity_str,
		AST_EVENT_IE_END);
}
