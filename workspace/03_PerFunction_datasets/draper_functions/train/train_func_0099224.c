setinfo_int (const char *key, const char * s, size_t len)
{
	char buf[10];
	int val;

	if (len > sizeof(buf)) len = sizeof(buf)-1;
	strncpy (buf, s, len);
	buf[len] = 0;
	val = atoi(buf);
	dstate_setinfo (key, "%d", val);
	return val;
}
