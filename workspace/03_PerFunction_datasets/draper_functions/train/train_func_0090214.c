free_list()
{
	gint i;
	gint j;
 	if(Nlist == 0 || NlistTitle == 0)
 	{
		init_list();
		return;
 	}
 	if(Titles)
	{
		for(i=0;i<NlistTitle;i++)
			if(Titles[i]) g_free(Titles[i]);
		g_free(Titles);
	}

	if(List)
	{
		for(i=0;i<Nlist;i++)
		{
			for(j=0;j<NlistTitle;j++)
					if(List[i][j]) g_free(List[i][j]);
			if(List[i]) g_free(List[i]);
		}
		g_free(List);
	}

	init_list();

}
