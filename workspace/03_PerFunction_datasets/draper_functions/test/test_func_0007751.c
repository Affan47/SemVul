MGD77_Set_Home (struct MGD77_CONTROL *F)
{
	char *this = NULL;

	if (F->MGD77_HOME) return;

	if ((this = getenv ("MGD77_HOME")) != CNULL) {
		F->MGD77_HOME = (char *) GMT_memory (VNULL, (size_t)(strlen (this) + 1), (size_t)1, "MGD77_Set_Home");
		strcpy (F->MGD77_HOME, this);
	}
	else {
		F->MGD77_HOME = (char *) GMT_memory (VNULL, (size_t)(strlen (GMT_SHAREDIR) + 7), (size_t)1, "MGD77_Set_Home");
		sprintf (F->MGD77_HOME, "%s/mgd77", GMT_SHAREDIR);
	}
#ifdef WIN32
	DOS_path_fix (F->MGD77_HOME);
#endif
}
