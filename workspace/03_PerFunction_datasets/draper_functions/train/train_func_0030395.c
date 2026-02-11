mbrola_is_idle(void)
{
	char *p;
	char buffer[20];


	if (lseek(mbr_proc_stat, 0, SEEK_SET) != 0)
		return 0;
	if (read(mbr_proc_stat, buffer, sizeof(buffer)) != sizeof(buffer))
		return 0;
	p = (char *)memchr(buffer, ')', sizeof(buffer));
	if (!p || (unsigned)(p - buffer) >= sizeof(buffer) - 2)
		return 0;
	return (p[1] == ' ' && p[2] == 'S');
}
