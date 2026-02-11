read_atom_hin_file(FILE* file,gchar* listFields[])
{
	guint taille = BSIZE;
	gchar t[BSIZE];
	gchar dump[BSIZE];
	gint i;

    	if(!fgets(t,taille,file)) return FALSE;
    	sscanf(t,"%s",dump);
	g_strdup(dump);
	if(strcmp(dump,"ATOM")!=0)
	{
		if(strcmp(dump,"RES")==0)
		{
    			sscanf(t,"%s %s %s",dump,dump,listFields[1]);
			sprintf(listFields[0],"Unknown");
		}
		else
			return FALSE;
	}
	else
	{


    		sscanf(t,"%s %s %s %s %s %s %s %s %s %s",dump,dump,listFields[0],listFields[1],listFields[2],dump,listFields[3],listFields[4],listFields[5],listFields[6]);
	}
	for(i=0;i<6;i++)
	{
		delete_last_spaces(listFields[i]);
		delete_first_spaces(listFields[i]);
	}
	return TRUE;

}
