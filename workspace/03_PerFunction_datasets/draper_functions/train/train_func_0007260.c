FS_CreatePath (char *path)
{
	char	*ofs;

	for (ofs = path+1 ; *ofs ; ofs++)
	{
		if (*ofs == '/')
		{
			*ofs = 0;
			Sys_Mkdir (path);
			*ofs = '/';
		}
	}
}
