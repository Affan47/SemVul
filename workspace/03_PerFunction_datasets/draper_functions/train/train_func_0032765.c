mne_copy(const MntEnt *src)
{
	MntEnt	*ne = NULL;
	gsize	s_fs, s_dir;

	if(src != NULL)
	{
		s_fs  = strlen(src->fsname) + 1;
		s_dir = strlen(src->dir) + 1;
		ne = g_malloc(sizeof *ne + s_fs + s_dir);
		ne->fsname = (gchar *) (ne + 1);
		ne->dir    = (gchar *) (ne + 1) + s_fs;
		strcpy(ne->fsname, src->fsname);
		strcpy(ne->dir, src->dir);
	}
	return ne;
}
