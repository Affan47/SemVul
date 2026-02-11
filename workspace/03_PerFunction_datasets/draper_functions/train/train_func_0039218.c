get_list_of_grids(gchar* fileName, gint *nE)
{
	FILE* file = FOpen(fileName, "rb");
	gboolean Ok = TRUE;
	gint len = BSIZE;
	gchar buffer[BSIZE];
	gchar** gridsList = NULL;
	gint n;
	gint i;
	gint j;

	*nE = 0;
	CancelCalcul = FALSE;
	if(!file)
	{
		sprintf(buffer,_("I can not open %s file\n, I read list of grids from this file"),fileName);
		Message(buffer,_("Error"),TRUE);
		return NULL;
	}
	while(!feof(file))
	{
		if(!fgets(buffer,len,file)) return NULL;
		if(strstr(buffer,"X") && strstr(buffer,"Y") && strstr(buffer,"Z"))
		{
			Ok = TRUE;
			break;
		}
	}
	if(!Ok) return NULL;
	delete_last_spaces(buffer);
	n = (strlen(buffer)+1)/13-3;
	if(n<1) return NULL;

	gridsList = g_malloc((n+1)*sizeof(gchar*));
	for(i=0;i<n;i++)
	{
		gridsList[i] = g_malloc((13+1)*sizeof(gchar));
		for(j=0;j<13;j++)
			gridsList[i][j] = buffer[13*3+i*13+j];
		gridsList[i][13] = '\0';
	}

	gridsList[n] = NULL;


	*nE = n;
	return gridsList;

}
