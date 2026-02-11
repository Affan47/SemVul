arcadia_vsync (void)
{
	static int cnt;

	cnt--;
	if (cnt > 0)
		return;
	cnt = 50;
	if (!nvwrite)
		return;
	nvram_write ();
	nvwrite = 0;
}
