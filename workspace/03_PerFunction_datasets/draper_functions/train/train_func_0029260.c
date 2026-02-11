maildir_setfile1(const char *name, int newmail, int omsgCount)
{
	int	i;

	if (!newmail)
		cleantmp(name);
	mb.mb_perm = Rflag ? 0 : MB_DELE;
	if ((i = subdir(name, "cur", newmail)) != 0)
		return i;
	if ((i = subdir(name, "new", newmail)) != 0)
		return i;
	append(name, NULL, NULL);
	for (i = newmail?omsgCount:0; i < msgCount; i++)
		readin(name, &message[i]);
	if (newmail) {
		if (msgCount > omsgCount)
			qsort(&message[omsgCount],
					msgCount - omsgCount,
					sizeof *message, mdcmp);
	} else {
		if (msgCount)
			qsort(message, msgCount, sizeof *message, mdcmp);
	}
	return msgCount;
}
