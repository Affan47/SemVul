nlstDirectory(FILE* fd, const SpoolDir& sd, DIR* dir)
{


    fxStr path(sd.pathname);
    struct dirent* dp;
    while ((dp = readdir(dir))) {
	if (dp->d_name[0] == '.' &&
	  (dp->d_name[1] == '\0' || strcmp(dp->d_name, "..") == 0))
	    continue;
	struct stat sb;
	if (!FileCache::update(path | dp->d_name, sb))
	    continue;
	if ((this->*sd.isVisibleFile)(dp->d_name, sb)) {
	    (this->*sd.nlstFile)(fd, sd, dp->d_name, sb);
	    fputs("\r\n", fd);
	}
    }
}
