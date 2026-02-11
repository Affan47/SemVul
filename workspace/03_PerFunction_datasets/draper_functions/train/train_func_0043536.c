crash_assert_logv(const char * const fmt, va_list ap)
{
	crash_mode();

	if (vars != NULL && vars->logstr != NULL) {
		const char *msg;


		ck_writable(vars->logck);
		str_vprintf(vars->logstr, fmt, ap);
		msg = str_2c(vars->logstr);
		ck_readonly(vars->logck);
		crash_set_var(message, msg);
		return msg;
	} else {
		static char msg[CRASH_MSG_SAFELEN];

		str_vbprintf(msg, sizeof msg, fmt, ap);
		return msg;
	}
}
