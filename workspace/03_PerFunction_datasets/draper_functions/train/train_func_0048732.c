tree_data_destroy_one_node (gint inode)
{
    gint ifdel = 0;
    gint ifn = 0;
    gint i;
    DataTree** tmp=NULL;


    if(AllFiles == NULL)
	return;

     for(i=0;i<Nfiles;i++)
     {
     	if(AllFiles[i]->itype == inode)
     	{
		ifdel++;
     		if(AllFiles[i]->projectname)
	 		g_free(AllFiles[i]->projectname);
     		if(AllFiles[i]->localdir)
	 		g_free(AllFiles[i]->localdir);
     		if(AllFiles[i]->remotehost)
	 		g_free(AllFiles[i]->remotehost);
     		if(AllFiles[i]->remoteuser)
	 		g_free(AllFiles[i]->remoteuser);
     		if(AllFiles[i]->remotepass)
	 		g_free(AllFiles[i]->remotepass);
     		if(AllFiles[i]->remotedir)
	 		g_free(AllFiles[i]->remotedir);
     		if(AllFiles[i]->command)
	 		g_free(AllFiles[i]->command);
      		AllFiles[i]->noeud=NULL;
      		AllFiles[i]->projectname=g_strdup("DELETED");
	}
      }

      if(Nfiles>ifdel)
      	tmp = g_malloc((Nfiles-ifdel)*sizeof(DataTree*));
      else
      {
      	Nfiles = 0;
      	if(AllFiles)
		g_free(AllFiles);
      	AllFiles = NULL;
      	return;
      }
      ifn =0;
      for(i=0;i<Nfiles;i++)
      {
     	if(AllFiles[i]->itype != inode)
     	{
         tmp[ifn]=AllFiles[i];
         ifn++;
        }
       }


      Nfiles = ifn;
      if(AllFiles)
      	g_free(AllFiles);
      AllFiles = tmp;

}
