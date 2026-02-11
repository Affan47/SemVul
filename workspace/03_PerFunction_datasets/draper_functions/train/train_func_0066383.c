getTempFileFD()
{
	if (tempfilefd > -1) {
		return tempfilefd;
	}
	tempfilepath = o.download_dir.c_str();
	tempfilepath += "/tfXXXXXX";
	char *tempfilepatharray = new char[tempfilepath.length() + 1];
	strcpy(tempfilepatharray, tempfilepath.toCharArray());
	if ((tempfilefd = mkstemp(tempfilepatharray)) < 0) {
#ifdef DGDEBUG
		std::cerr << "error creating temp " << tempfilepath << ": " << strerror(errno) << std::endl;
#endif
		syslog(LOG_ERR, "Could not create temp file to store download for scanning: %s", strerror(errno));
		tempfilefd = -1;
		tempfilepath = "";
	} else {
		tempfilepath = tempfilepatharray;
	}
	delete[]tempfilepatharray;
	return tempfilefd;
}
