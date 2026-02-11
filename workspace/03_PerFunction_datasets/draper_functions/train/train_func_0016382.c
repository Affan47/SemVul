set_properties(GtkWidget *Win,gpointer data)
{
	DataTree*  newdata = NULL;
	DataTree*  olddata = (DataTree*)(g_object_get_data(G_OBJECT(Win),"Data"));
	GtkWidget **entrys = (GtkWidget **)(g_object_get_data(G_OBJECT(Win),"Entrys"));
	GtkWidget **buttons =(GtkWidget **)(g_object_get_data(G_OBJECT(Win),"Buttons"));

	GtkWidget * buttonSsh = g_object_get_data(G_OBJECT(Win),"ButtonSsh");


	gchar* remotehost = NULL;
	gchar* remoteuser = NULL;
	gchar* remotepass = NULL;
	gchar* remotedir  = NULL;
	GabEditNetWork netWorkProtocol ;


	if (GTK_TOGGLE_BUTTON (buttons[0])->active)
	{
		remotehost = g_strdup("");
		remoteuser = g_strdup("");
		remotepass  = g_strdup("");
		remotedir  = g_strdup("");
	}
	else
	{
		remotehost = g_strdup(gtk_entry_get_text(GTK_ENTRY(entrys[0])));
		remoteuser = g_strdup(gtk_entry_get_text(GTK_ENTRY(entrys[1])));
		remotepass = g_strdup(gtk_entry_get_text(GTK_ENTRY(entrys[2])));
		remotedir  = g_strdup(gtk_entry_get_text(GTK_ENTRY(entrys[3])));
	}
	if (GTK_TOGGLE_BUTTON (buttonSsh)->active) netWorkProtocol = GABEDIT_NETWORK_SSH;
	else netWorkProtocol = GABEDIT_NETWORK_FTP_RSH;


   	newdata = tree_data_new (
			olddata->projectname,olddata->datafile,olddata->localdir,
			remotehost,remoteuser,remotepass,remotedir,
			olddata->itype, olddata->command, netWorkProtocol);
	if(remotehost) g_free(remotehost);
	if(remoteuser) g_free(remoteuser);
	if(remotepass) g_free(remotepass);
	if(remotedir) g_free(remotedir);

	clear_one_project();
	AddFeuille(GTK_TREE_VIEW(treeViewProjects),noeud[newdata->itype],newdata);
   	if(Nfiles==0)
      		AllFiles = g_malloc(sizeof(DataTree*));
    	else
      		AllFiles = (DataTree**)g_realloc(AllFiles,(Nfiles+1)*sizeof(DataTree*));
    Nfiles++;
    AllFiles[Nfiles-1] = newdata;
	if(  strcmp(fileopen.projectname,newdata->projectname)==0
	  && strcmp(fileopen.localdir,newdata->localdir)==0
	  )
	{
		set_fileopen(newdata);
 		change_all_labels();
	}
}
