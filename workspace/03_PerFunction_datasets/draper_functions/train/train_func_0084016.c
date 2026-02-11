is_metafile(char *name)
{
    int i = 0;
    char *p = NULL;

    if((p = strrchr(name,'.'))) {
	p++;
	for(i = 0; i < sizeof(metafile_prefixes)/sizeof(char *) ; i++) {
	    if(!strcasecmp(metafile_prefixes[i],p)) return 1;
	}
    }

    if((p = strrchr(name,'/'))) {
	p++;
	for(i = 0; i < sizeof(metafile_starts)/sizeof(char *) ; i++) {
	    if(!strncasecmp(metafile_starts[i],p,strlen(metafile_starts[i]))) return 1;
	}
    }

    return 0;
}
