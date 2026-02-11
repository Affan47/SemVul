chkmail(force)
bool	force;
{
	time_t	now;
	static bool	state = NO;
	static time_t	last_chk = 0,
			mbox_time = 0;
	struct stat	stbuf;

	if (MailInt == 0 || Mailbox[0] == '\0')
		return NO;

	time(&now);
	if ((force == NO) && (now < last_chk + MailInt))
		return state;

	last_chk = now;
	if (stat(Mailbox, &stbuf) < 0) {
		state = NO;
		return NO;
	}
	if ((stbuf.st_atime > stbuf.st_mtime && stbuf.st_atime > mbox_time)
	|| stbuf.st_size == 0)
	{
		mbox_time = stbuf.st_atime;
		state = NO;
	} else if (stbuf.st_mtime > mbox_time) {
		if (mbox_time > 0)
			dobell(2);
		mbox_time = stbuf.st_mtime;
		state = YES;
	}
	return state;
}
