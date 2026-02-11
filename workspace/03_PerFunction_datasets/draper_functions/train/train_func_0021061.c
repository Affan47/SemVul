audit_log_rule_change(char *action, struct audit_krule *rule, int res)
{
	struct audit_buffer *ab;
	uid_t loginuid = from_kuid(&init_user_ns, audit_get_loginuid(current));
	unsigned int sessionid = audit_get_sessionid(current);

	if (!audit_enabled)
		return;

	ab = audit_log_start(NULL, GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	if (!ab)
		return;
	audit_log_format(ab, "auid=%u ses=%u" ,loginuid, sessionid);
	audit_log_task_context(ab);
	audit_log_format(ab, " op=");
	audit_log_string(ab, action);
	audit_log_key(ab, rule->filterkey);
	audit_log_format(ab, " list=%d res=%d", rule->listnr, res);
	audit_log_end(ab);
}
