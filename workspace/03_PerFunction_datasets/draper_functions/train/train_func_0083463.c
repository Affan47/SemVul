ng_plugins(char *dirname)
{
    struct dirent **list;
    char filename[1024];
    void *plugin;
    void (*initcall)(void);
    int i,n = 0,l = 0;

    n = scandir(dirname,&list,NULL,alphasort);
    if (n <= 0)
	return 0;
    for (i = 0; i < n; i++) {
	if (0 != fnmatch("*.so",list[i]->d_name,0))
	    continue;
	sprintf(filename,"%s/%s",dirname,list[i]->d_name);
	if (NULL == (plugin = dlopen(filename,RTLD_NOW))) {
	    fprintf(stderr,"dlopen: %s\n",dlerror());
	    continue;
	}
	if (NULL == (initcall = dlsym(plugin,"ng_plugin_init"))) {
	    if (NULL == (initcall = dlsym(plugin,"_ng_plugin_init"))) {
		fprintf(stderr,"dlsym[%s]: %s\n",filename,dlerror());
		continue;
	    }
	}
	initcall();
	l--;
    }
    for (i = 0; i < n; i++)
	free(list[i]);
    free(list);
    return l;
}
