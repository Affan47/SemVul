read_gabedit_files(GabeditFileChooser *SelecFile, gint response_id)
{
	gchar *fileName;
	GSList* lists = NULL;
	GSList* cur = NULL;

	if(response_id != GTK_RESPONSE_OK) return;

	lists = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(SelecFile));

	stopAnimation(NULL, NULL);

	freeAnimationGrids();
	cur = lists;
	animationGrids.numberOfFiles = 0;
	while(cur != NULL)
	{
		animationGrids.numberOfFiles++;
		cur = cur->next;
	}
	if(animationGrids.numberOfFiles>0)
	{
		gint k = 0;
		animationGrids.geometries = g_malloc(animationGrids.numberOfFiles*sizeof(GeomGrid));
		animationGrids.fileNames = g_malloc(animationGrids.numberOfFiles*sizeof(gchar*));
		animationGrids.grids = g_malloc(animationGrids.numberOfFiles*sizeof(Grid*));
		for(k=0;k<animationGrids.numberOfFiles;k++)
		{
			animationGrids.fileNames[k] = NULL;
			animationGrids.grids[k] = NULL;
			animationGrids.geometries[k].numberOfAtoms = 0;
			animationGrids.geometries[k].listOfAtoms = NULL;
		}
		k = 0;
		cur = lists;
		while(cur != NULL)
		{
			fileName = (gchar*)(cur->data);

			if(read_gauss_molpro_cube_orbitals_file(fileName,0,0,GABEDIT_TYPEFILE_CUBEGABEDIT, FALSE))
			{
				set_geometry(k);
				animationGrids.fileNames[k] = g_strdup(fileName);
				animationGrids.grids[k] = copyGrid(grid);
			       	k++;
			}
			cur = cur->next;
		}
		if(k<=0)
		{
			freeAnimationGrids();
		}
		else
		if(k!=animationGrids.numberOfFiles)
		{
			animationGrids.numberOfFiles = k;
			animationGrids.geometries = g_realloc(animationGrids.geometries, animationGrids.numberOfFiles*sizeof(GeomGrid));
			animationGrids.fileNames = g_realloc(animationGrids.fileNames, animationGrids.numberOfFiles*sizeof(gchar*));
			animationGrids.grids = g_realloc(animationGrids.grids, animationGrids.numberOfFiles*sizeof(Grid*));
		}
		if(k>0)
		{
			animationGrids.typeOfFile = GABEDIT_TYPEFILE_CUBEDX;
		}
	}
  	rafreshList();

}
