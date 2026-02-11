is_same_file (struct DCC *dcc, struct DCC *new_dcc)
{
#ifndef WIN32
	GStatBuf st_a, st_b;
#endif


	if (strcmp (dcc->destfile, new_dcc->destfile) == 0)
		return TRUE;


#ifdef WIN32

#else

	if ((dcc->fp == -1 ? g_stat (dcc->destfile, &st_a) : fstat (dcc->fp, &st_a)) == -1)
		return FALSE;
	if (g_stat (new_dcc->destfile, &st_b) == -1)
		return FALSE;


	if (st_a.st_ino == st_b.st_ino &&
		 st_a.st_dev == st_b.st_dev)
		return TRUE;
#endif

	return FALSE;
}
