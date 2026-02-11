createDirectory ( const char* name )
{
   #ifdef _UNIX_
    char *nname;
    int i;

    if (name == NULL || (nname=strdup(name)) == NULL)
	return -1;
    i = strlen(nname);

    while (i>1 && nname[i-1] == '/')
		nname[--i] = '\0';
    i = mkdir ( nname, 0700 );
    free(nname);

    return i;
   #else
    return mkdir ( name );
   #endif
}
