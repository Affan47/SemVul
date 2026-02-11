clog_msg_start_err()
{
	if (!log_opened)
		clog_open_stderr("init");
	strcpy(logbuf, "ERR: ");
}
