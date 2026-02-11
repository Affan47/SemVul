host_opendir( const char *fpathName ) {
	DIR *result = opendir( fpathName );
	if ( result || errno != ENOTDIR )
		return result;


	struct stat statBuf;
	if ( !lstat(fpathName, &statBuf) && S_ISLNK(statBuf.st_mode) ) {
		char temp[MAXPATHNAMELEN];
		if (host_readlink(fpathName,temp,sizeof(temp)-1))
			return host_opendir( temp );
	}

	return NULL;
}
