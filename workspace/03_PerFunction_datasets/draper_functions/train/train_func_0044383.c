makeLock( const char* lockName )
{
	char name[CL_MAX_DIR];

	if ( !lockPrefix.empty() ) {
		cl_sprintf(name, CL_MAX_DIR, "%s-%s", lockPrefix.c_str(), lockName);
	} else {
		cl_strcpy(name,lockName,CL_MAX_DIR);
	}

	return _CLNEW FSLock( lockDir.c_str(), name, this->filemode );
}
