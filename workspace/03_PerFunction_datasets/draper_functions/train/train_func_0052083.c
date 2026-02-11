prDIRS()
{
	register List	*lp;

	s_mess(ProcFmt);
	for (lp = DirStack; lp != NULL; lp = list_next(lp))
		add_mess("%s ", pr_name(dir_name(lp), YES));
}
