handle_standby_sig_alarm(SIGNAL_ARGS)
{
	int			save_errno = errno;

	if (standby_timeout_active)
		(void) CheckStandbyTimeout();

	errno = save_errno;
}
