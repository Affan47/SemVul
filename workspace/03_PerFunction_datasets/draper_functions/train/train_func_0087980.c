crash_append_error(const char * const msg)
{
	crash_mode();

	if (vars != NULL && vars->logck != NULL) {
		const char *m;


		ck_writable(vars->logck);
		str_ncat_safe(vars->logstr, msg, strlen(msg));
		m = str_2c(vars->logstr);
		ck_readonly(vars->logck);
		crash_set_var(message, m);
	}
}
