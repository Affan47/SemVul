resolveSymlinks( char * path ) {
	char * ch;
	if(path == NULL)
		return path;

	ch = path;
    path = realpath(path, NULL);
    if (path == NULL)
    	return ch;
    return path;
}
