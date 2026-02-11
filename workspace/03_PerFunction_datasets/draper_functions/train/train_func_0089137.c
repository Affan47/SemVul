R_BeginRegistration (char *model)
{
	char	fullname[MAX_OSPATH];
 	char    *path;
	cvar_t	*flushmap;
	FILE	*file;
	int		i;

	registration_sequence++;
	r_oldviewcluster = -1;

	r_weather = 0;
	r_nosun = 0;


	path = NULL;
	map_fog = false;
	r_weather = false;
	r_nosun = false;
	r_sunX = 0;
	r_sunY = 0;
	r_sunZ = 0;
	for(;;)
	{
		path = FS_NextPath( path );
		if( !path )
		{
			break;
		}
		Com_sprintf(fullname, sizeof(fullname), "%s/maps/scripts/%s.fog", path, model);
		i = 0;
		R_FindFile( fullname, &file );
		if(file) {

			fclose(file);
			R_ReadFogScript(fullname);
			break;
		}
	}


	strcpy(map_music, "music/menumusic.ogg");
	strcpy(map_music_sec, "music/adrenaline.ogg");
	S_RegisterSound (map_music_sec);
	path = NULL;
	for(;;)
	{
		path = FS_NextPath( path );
		if( !path )
		{
			break;
		}
		Com_sprintf(fullname, sizeof(fullname), "%s/maps/scripts/%s.mus", path, model);
		i = 0;
		R_FindFile( fullname, &file );
		if(file)
		{

			fclose( file );
			R_ReadMusicScript( fullname );
			break;
		}
	}

	r_gotFlag = false;
	r_lostFlag = false;
	Cvar_Set("rs_hasflag", "0");

	Com_sprintf (fullname, sizeof(fullname), "maps/%s.bsp", model);


	flushmap = Cvar_Get ("flushmap", "0", 0);

	if ( strcmp(mod_known[0].name, fullname) || flushmap->value)
		Mod_Free (&mod_known[0]);
	else
		Mod_Free (&mod_known[0]);

	r_worldmodel = Mod_ForName(fullname, true);

	r_viewcluster = -1;

	r_teamColor = 0;

	R_RegisterLightGroups();


	RGD_BuildWorldTrimesh ();


	if(gl_state.vbo)
		VB_BuildWorldVBO();
}
