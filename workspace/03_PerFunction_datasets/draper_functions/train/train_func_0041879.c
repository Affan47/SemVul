dirscan(char *path, struct vpp_filename *fn)
{
DIR *dp = opendir(path);
struct dirent *dirp;
int pathlen = strlen(path);
int nument = 0;
struct stringchain_t *sc=NULL, *sct;
int i;

if(dp)
	{
	while((dirp=readdir(dp)))
		{
		char *fullpath = malloc(pathlen + 1 + strlen(dirp->d_name) + 1);
		struct stat buf;

		sprintf(fullpath, "%s/%s", path, dirp->d_name);
		if(!stat(fullpath, &buf))
			{
			if(S_ISREG(buf.st_mode))
				{
				sct = (struct stringchain_t *)calloc(1, sizeof(struct stringchain_t));
				sct->name = strdup(dirp->d_name);
				sct->next = sc;
				sc = sct;
				nument++;
				}
			}
		free(fullpath);
		}

	if(nument)
		{
		fn->numchildren = nument;
		fn->children = malloc(nument*sizeof(char *));

		for(i=0;i<nument;i++)
			{
			fn->children[i] = sc->name;
			sct = sc->next;
			free(sc);
			sc = sct;
			}

		qsort(fn->children, nument, sizeof(char **), compar_cstarstar);
		}
	}

return(dp!=NULL);
}
