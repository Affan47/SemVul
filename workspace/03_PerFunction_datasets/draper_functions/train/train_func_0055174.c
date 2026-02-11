bfuse_getattr(const char *path, struct stat *st)
{
	memset(st, 0, sizeof(*st));

	if( Directory *dir = FindDir(path) ) {
		dir->FillDirStat(st);
		return 0;
	}
	else if( File *file = FindFile(path) ) {
		file->FillFileStat(path, st);
		return 0;
	}
	else
		return -ENOENT;
}
