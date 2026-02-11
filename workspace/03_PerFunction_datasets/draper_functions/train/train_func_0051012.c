read_basis_from_a_molpro_output_file(gchar *FileName,gint* nbasis,long int pos)
{
 	gchar **strbasis;
 	gchar *t;
 	FILE *fd;
 	gint taille=BSIZE;
 	gint nrows=0;
 	gint i=0;
	OneBasis* Basis;
	long int n = -1;
	gboolean OK = FALSE;

 	if ((!FileName) || (strcmp(FileName,"") == 0))
 	{
		Message(_("Sorry No file selected\n"),_("Error"),TRUE);
    		return NULL;
 	}

 	fd = FOpen(FileName, "rb");
 	if(fd ==NULL)
 	{
		gchar buffer[BSIZE];
		sprintf(buffer,_("Sorry, I can not open '%s' file\n"),FileName);
  		Message(buffer,_("Error"),TRUE);
  		return NULL;
 	}

 	t=g_malloc(taille);
 	while(!feof(fd))
	{
    		{ char* e = fgets(t,taille,fd);}
		n++;
		if(n==pos)
		{
			OK = TRUE;
			break;
		}
        }
	if(!OK)
	{
		g_free(t);
  		Message(_("Sorry I can read basis in this file\n"),_("Error"),TRUE);
  		return NULL;
	}
    	{ char* e = fgets(t,taille,fd);}
    	{ char* e = fgets(t,taille,fd);}
    	{ char* e = fgets(t,taille,fd);}

	strbasis=g_malloc(sizeof(gchar*));
 	while(!feof(fd))
	{
    		{ char* e = fgets(t,taille,fd);}
		if(this_is_a_backspace(t))
			break;
		nrows++;
		strbasis = g_realloc(strbasis,nrows*sizeof(gchar*));
		strbasis[nrows-1] = g_strdup(t);
	}
	if(nrows == 0)
	{
		g_free(t);
		g_free(strbasis);
  		Message(_("Sorry I can read basis in this file\n"),_("Error"),TRUE);
  		return NULL;
	}


	Basis = get_basis_from_strbasis(strbasis,nrows,nbasis);
	for(i=0;i<nrows;i++)
		g_free(strbasis[i]);
	g_free(strbasis);
 	fclose(fd);
 	g_free(t);
	if(Type) g_free(Type);
	Type = NULL;
	return Basis;
}
