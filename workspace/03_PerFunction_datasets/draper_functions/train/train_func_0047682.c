SV_Map_f (void)
{
	char	*map;
	char	expanded[MAX_QPATH];


	map = Cmd_Argv(1);
	if (!strstr (map, "."))
	{
		Com_sprintf (expanded, sizeof(expanded), "maps/%s", map);
		if (FS_LoadFile (expanded, NULL) == -1)
		{
			Com_sprintf (expanded, sizeof(expanded), "maps/%s.bsp", map);
			if (FS_LoadFile (expanded, NULL) == -1)
			{
				Com_Printf ("Cannot find %s\n", expanded);
				return;
			}
		}
	}


	SV_Map (false, Cmd_Argv(1), false );


	strncpy (svs.mapcmd, Cmd_Argv(1), sizeof(svs.mapcmd)-1);
}
