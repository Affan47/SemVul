pg_tzenumerate_end(pg_tzenum *dir)
{
	while (dir->depth >= 0)
	{
		FreeDir(dir->dirdesc[dir->depth]);
		pfree(dir->dirname[dir->depth]);
		dir->depth--;
	}
	pfree(dir);
}
