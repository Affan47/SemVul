SV_WipeSavegame (const char *savename)
{
	char	name[MAX_OSPATH];
	char	*s;

	Com_DPrintf("SV_WipeSaveGame(%s)\n", savename);

	Com_sprintf (name, sizeof(name), "%s/save/%s/server.ssv", FS_Gamedir (), savename);
	FS_RemoveFile(name);
	Com_sprintf (name, sizeof(name), "%s/save/%s/game.ssv", FS_Gamedir (), savename);
	FS_RemoveFile(name);

	Com_sprintf (name, sizeof(name), "%s/save/%s/*.sav", FS_Gamedir (), savename);
	s = Sys_FindFirst( name, 0, 0 );
	while (s)
	{
		FS_RemoveFile(s);
		s = Sys_FindNext( 0, 0 );
	}
	Sys_FindClose ();
	Com_sprintf (name, sizeof(name), "%s/save/%s/*.sv2", FS_Gamedir (), savename);
	s = Sys_FindFirst(name, 0, 0 );
	while (s)
	{
		FS_RemoveFile(s);
		s = Sys_FindNext( 0, 0 );
	}
	Sys_FindClose ();
}
