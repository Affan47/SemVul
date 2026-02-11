FS_ExecConfig (const char *filename)
{
	const char *dir;
	char name[MAX_QPATH];

	dir = Cvar_VariableString("gamedir");
	if (*dir)
		Com_sprintf(name, sizeof(name), "%s/%s/%s", fs_basedir->string, dir, filename);
	else
		Com_sprintf(name, sizeof(name), "%s/%s/%s", fs_basedir->string, BASEDIRNAME, filename);
	if (Sys_FindFirst(name, 0, SFF_SUBDIR | SFF_HIDDEN | SFF_SYSTEM))
		Cbuf_AddText (va("exec %s\n", filename));
	Sys_FindClose();
}
