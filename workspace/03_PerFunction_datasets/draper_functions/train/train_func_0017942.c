check_uamname(const char * uam)
{
	char * p;
	for (p=uam;*p;p++) {
		if (*p==' ') continue;
		if ((*p<'A') || (*p>'z')) return -1;
	}
	return 0;
}
