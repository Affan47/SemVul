seelink ( path, buff, size)
char * path ;
char * buff ;
int size    ;
{
#if defined(_WIN32)
	strcpy(buff, path);
	return (strlen(path));
#else
	char *cp ;
	char filename[MAXFILENAMSIZE] ;
	char storpath[MAXFILENAMSIZE] ;
	char stordir[MAXFILENAMSIZE] ;
	int n ;

	strcpy(storpath, path );
	if ( (cp = strrchr(storpath,'/')) != NULL ) {
		strcpy(filename,cp+1) ;
		cp[0] = '\0' ;
	}
	else
		return -1 ;

	while ((cp = getcwd(stordir, MAXFILENAMSIZE-1)) == NULL && errno == ETIMEDOUT)
		sleep (60);
	if ( chdir(storpath)  < 0 ) {
		errno = ENOENT ;
		return -1 ;
	}
	else {
		cp = getcwd( buff, size );
		chdir(stordir);
		if ( cp == NULL )
			return -1 ;
		else {


			strcat (buff,"/") ;
			strcat (buff ,filename) ;
			strcpy(filename, buff ) ;
			if ( (n=readlink( filename, buff, size)) < 0 )
				return (strlen(filename) ) ;
			else {
				buff[n] = '\0' ;
				return ( strlen(buff) ) ;
			}
		}
	}
#endif
}
