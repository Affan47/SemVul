status_msg_set(unsigned const char *msg, int len)
{
	register int	i;

	for (i = 0; i < status_line[WAIT_REGION].len; i++) {
		status_add(M0+i, len ? msg[i] : nullblank, KT_STD);
		if (len)
			len--;
	}
}
