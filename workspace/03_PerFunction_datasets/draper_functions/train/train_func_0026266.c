str_to_monitor_policy(const char * const value)
{
	if (!strcasecmp(value, "never")) {
		return AST_CC_MONITOR_NEVER;
	} else if (!strcasecmp(value, "native")) {
		return AST_CC_MONITOR_NATIVE;
	} else if (!strcasecmp(value, "generic")) {
		return AST_CC_MONITOR_GENERIC;
	} else if (!strcasecmp(value, "always")) {
		return AST_CC_MONITOR_ALWAYS;
	} else {
		ast_log(LOG_WARNING, "%s is an invalid value for cc_monitor_policy. Switching to 'never'\n", value);
		return AST_CC_MONITOR_NEVER;
	}
}
