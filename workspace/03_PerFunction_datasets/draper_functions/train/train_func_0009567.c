resume_console(void)
{
	if (!console_suspend_enabled)
		return;
	down_console_sem();
	console_suspended = 0;
	console_unlock();
}
