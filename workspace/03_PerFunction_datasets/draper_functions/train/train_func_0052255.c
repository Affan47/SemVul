R_RegisterCustomPlayerModels( void )
{
	char	mod_filename[MAX_QPATH];
	char	scratch[MAX_QPATH];
	int i, j;
	int npms = 0;
	int nskins = 0;
	char **dirnames;
	char **skinnames;

	dirnames = FS_ListFilesInFS( "players/*.*", &npms, SFF_SUBDIR, 0 );

	if ( !dirnames )
		return;

	if ( npms > 1024 )
		npms = 1024;

	for(i = 0; i < npms; i++)
	{
		if ( dirnames[i] == 0 )
			continue;

		Com_Printf("Registering custom player model: %s\n", dirnames[i]);
		Com_sprintf( mod_filename, sizeof(mod_filename), "%s/tris.md2", dirnames[i]);
		if(FS_FileExists(mod_filename))
			R_RegisterModel(mod_filename);
		else
			continue;
		Com_sprintf( mod_filename, sizeof(mod_filename), "%s/lod1.md2", dirnames[i]);
		if(FS_FileExists(mod_filename))
			R_RegisterModel(mod_filename);
		Com_sprintf( mod_filename, sizeof(mod_filename), "%s/lod2.md2", dirnames[i]);
		if(FS_FileExists(mod_filename))
			R_RegisterModel(mod_filename);


		for (j = 0; j < WModelsCount; j++)
		{
			Com_sprintf( mod_filename, sizeof(mod_filename), "%s/%s", dirnames[i], BaseWModels[j]);
			if(FS_FileExists(mod_filename))
				R_RegisterModel(mod_filename);
		}


		S_RegisterSoundsForPlayer (dirnames[i]);


		strcpy( scratch, dirnames[i] );
		strcat( scratch, "/*.jpg" );
		skinnames = FS_ListFilesInFS( scratch, &nskins, 0,
		    SFF_SUBDIR | SFF_HIDDEN | SFF_SYSTEM );

		if(!skinnames) {

			strcpy( scratch, dirnames[i] );
			strcat( scratch, "/*.tga" );
			skinnames = FS_ListFilesInFS( scratch, &nskins, 0,
				SFF_SUBDIR | SFF_HIDDEN | SFF_SYSTEM );
		}

		if(!skinnames)
			continue;

		for(j = 0; j < nskins; j++)
			R_RegisterSkin (skinnames[j]);

		if(skinnames)
			free(skinnames);

	}
	if(dirnames)
		free(dirnames);
}
