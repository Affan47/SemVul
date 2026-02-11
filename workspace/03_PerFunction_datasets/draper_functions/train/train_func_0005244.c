trywm(const char *path) {
	struct windowmanager *wm;
	const char *lastpart;

	if( path == NULL )
		return FALSE;

	for( wm = windowmanagers; wm != NULL ; wm = wm->next ) {
		if(strcmp(wm->path,path) == 0) {
			wm->isdefault = TRUE;
			return TRUE;
		}
	}
	lastpart = strrchr(path,'/');
	if( lastpart == NULL )
		lastpart = path;
	else
		lastpart++;

	for( wm = windowmanagers; wm != NULL ; wm = wm->next ) {
		const char *wmlastpart;

		wmlastpart = strrchr(wm->path,'/');
		if( wmlastpart == NULL )
			wmlastpart = wm->path;
		else
			wmlastpart++;

		if(strcmp(wmlastpart,lastpart) == 0) {
			wm->isdefault = TRUE;
			return TRUE;
		}
	}

	if( wmexists(path) ) {
		const char *wmbasename;

		wmbasename = strrchr(path,'/');
		if( wmbasename == NULL || wmbasename[1] == '\0' )
			wmbasename = path;
		else
			wmbasename++;

		wm = addwm(wmbasename, path, NULL);
		if( wm != NULL ) {
			wm->isdefault = TRUE;
			fprintf(stderr, "Added '%s' to list of window managers, as it is the configured default.\n", path);
			return true;
		}
	}
	return FALSE;
}
