scanSubDirs(s)
String s;
{
    DIR *dir;
    struct dirent *entry;
    struct stat statb;
    int save;

    if ((dir = opendir(searchBuf)) == NULL)
	errno = 0;
    else {
	searchChr(SLASH);
	save = searchPos;
	while ((entry = readdir(dir)) != NULL)
            if (entry->d_name[0] != '.') {
		searchStr(entry->d_name);
		if (stat(searchBuf, &statb)==0 && S_ISDIR(statb.st_mode)) {
		    searchChr(SLASH);
		    if (find2(s)) {
			closedir(dir);
			return TRUE;
		    }
		}
		searchReset(save);
	    }
	closedir(dir);
    }
    return FALSE;
}
