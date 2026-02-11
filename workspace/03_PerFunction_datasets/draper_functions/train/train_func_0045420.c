us_time(void)
{
	GTimeVal *tod;
	tod = g_new0(GTimeVal, 1);
	g_get_current_time(tod);
	ULLONG ust = (DWORD) tod->tv_sec * G_USEC_PER_SEC + (DWORD) tod->tv_usec;
	g_free(tod);
	return (ust);
}
