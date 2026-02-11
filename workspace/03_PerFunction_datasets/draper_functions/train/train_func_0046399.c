testtime_write(struct ast_channel *chan, const char *cmd, char *var, const char *value)
{
	struct ast_tm tm;
	struct timeval tv;
	char *remainder, result[30], timezone[80];


	if (!pbx_checkcondition(value)) {
		pbx_builtin_setvar_helper(chan, "TESTTIME", NULL);
		return 0;
	}


	if (!(remainder = ast_strptime(value, "%Y/%m/%d %H:%M:%S", &tm))) {
		return -1;
	}
	sscanf(remainder, "%79s", timezone);
	tv = ast_mktime(&tm, S_OR(timezone, NULL));

	snprintf(result, sizeof(result), "%ld", (long) tv.tv_sec);
	pbx_builtin_setvar_helper(chan, "__TESTTIME", result);
	return 0;
}
