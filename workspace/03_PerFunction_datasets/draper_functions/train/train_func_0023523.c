SV_ReadLevelFile (void)
{
	char	name[MAX_OSPATH];
	fileHandle_t f;

	Com_DPrintf("SV_ReadLevelFile()\n");

	Com_sprintf (name, sizeof(name), "save/current/%s.sv2", sv.name);
	FS_FOpenFile( name, &f, FS_MODE_READ|FS_TYPE_REAL );
	if (!f) {
		Com_Printf ("Failed to open %s\n", name);
		return;
	}
	FS_Read (sv.configstrings, sizeof(sv.configstrings), f);
	*( ( byte * )sv.configstrings + sizeof( sv.configstrings ) - 1 ) = 0;

	CM_ReadPortalState (f);
	FS_FCloseFile(f);

	Com_sprintf (name, sizeof(name), "%s/save/current/%s.sav", FS_Gamedir(), sv.name);
	ge->ReadLevel (name);
}
