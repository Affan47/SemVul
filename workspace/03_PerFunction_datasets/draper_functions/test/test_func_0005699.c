DirectoryMgrOpen(path,c_func,f_func,f_data,free_data)
char *path;
PFI c_func,f_func;
char *f_data;
int free_data;
{
	DirectoryMgr *dm;

	dm = (DirectoryMgr *)calloc(1,sizeof(DirectoryMgr));
	if (dm == NULL)
	{
		fprintf(stderr,"DirectoryMgrOpen: out of memory\n");
		if (free_data && f_data) free(f_data);
		return(NULL);
	}
	if (DirectoryOpen(path,DirectoryMgrDir(dm)) == FALSE)
	{
		fprintf(stderr,"DirectoryMgrOpen: can't open dir '%s'\n",
			DirectoryMgrDir(dm));
		free(dm);
		if (free_data && f_data) free(f_data);
		return(NULL);
	}
	DirectoryMgrCompFunc(dm) = c_func;
	DirectoryMgrRefilter(dm,f_func,f_data,free_data);
	return(dm);
}
