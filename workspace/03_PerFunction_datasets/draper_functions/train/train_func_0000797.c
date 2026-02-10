gethomedir(int *l)
{
    static char *home = NULL;
    static short hlen = 0;

    if(home == NULL){
	char buf[NLINE];

#ifndef _WINDOWS
	strncpy(buf, "~", sizeof(buf));
	buf[sizeof(buf)-1] = '\0';
	fixpath(buf, sizeof(buf));
#else
	if(Pmaster && Pmaster->home_dir)
	  snprintf(buf, sizeof(buf), "%s", Pmaster->home_dir);
	else
	  snprintf(buf, sizeof(buf), "%c:\\", _getdrive() + 'A' - 1);
#endif
	hlen = strlen(buf);
	if((home = (char *)malloc((hlen + 1) * sizeof(char))) == NULL){
	    emlwrite("Problem allocating space for home dir", NULL);
	    return(0);
	}

	strncpy(home, buf, hlen);
	home[hlen] = '\0';
    }

    if(l)
      *l = hlen;

    return(home);
}
