reread (int f, char *errmsg)
{
	if (lseek(f, 0L, 0) == 0 && read(f, procbuf, sizeof(procbuf) - 1) > 0)
		return;
	perror(errmsg);
	exit(1);
}
