clearredir(int drop)
{
	for (;;) {
		g_nullredirs = 0;
		if (!redirlist)
			break;
		popredir(drop,  0);
	}
}
