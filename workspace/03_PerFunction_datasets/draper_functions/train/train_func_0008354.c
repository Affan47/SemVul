set_last_directory(G_CONST_RETURN gchar* FileName)
{
	gchar* temp = get_suffix_name_file(FileName);
	gchar* localdir = get_name_dir(temp);
	if(!localdir) return;
	if(lastdirectory) g_free(lastdirectory);
	lastdirectory = g_strdup(localdir);
	if(temp) g_free(temp);
	if(localdir) g_free(localdir);
	if(lastdirectory && gabedit_directory() && strcmp(lastdirectory,gabedit_directory()))
		{int it = chdir(lastdirectory);}
}
