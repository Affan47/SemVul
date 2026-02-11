scheduled_destroy(const void *vid)
{
	unsigned short callno = PTR_TO_CALLNO(vid);
	ast_mutex_lock(&iaxsl[callno]);
	if (iaxs[callno]) {
		ast_debug(1, "Really destroying %d now...\n", callno);
		iax2_destroy(callno);
	}
	ast_mutex_unlock(&iaxsl[callno]);
	return 0;
}
