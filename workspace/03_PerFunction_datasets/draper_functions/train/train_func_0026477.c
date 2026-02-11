mdtmCmd(const char* pathname)
{
    struct stat sb;
    SpoolDir* dir = fileAccess(pathname, X_OK, sb);
    if (dir) {
	struct tm* t = cvtTime(sb.st_mtime);
	reply(213, "%d%02d%02d%02d%02d%02d"
	    , t->tm_year+1900
	    , t->tm_mon+1
	    , t->tm_mday
	    , t->tm_hour
	    , t->tm_min
	    , t->tm_sec
	);
    }
}
