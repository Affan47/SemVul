opal_os_dirpath_is_empty(const char *path ) {
#ifndef __WINDOWS__
    DIR *dp;
    struct dirent *ep;

    if (NULL != path) {
    	dp = opendir(path);
    	if (NULL != dp) {
    	    while ((ep = readdir(dp))) {
        		if ((0 != strcmp(ep->d_name, ".")) &&
        		    (0 != strcmp(ep->d_name, ".."))) {
                            closedir(dp);
        		    return false;
        		}
    	    }
    	    closedir(dp);
    	    return true;
    	}
    	return false;
    }

    return true;
#else
    char search_path[MAX_PATH];
    HANDLE file;
    WIN32_FIND_DATA file_data;
    bool found = false;

    if (NULL != path) {
        strncpy(search_path, path, strlen(path)+1);
        strncat (search_path, "\\*", 3);

        file = FindFirstFile(search_path, &file_data);
        if (INVALID_HANDLE_VALUE == file) {
            goto cleanup;
        }

        do {
            if (0 != strcmp(file_data.cFileName, ".") || 0 != strcmp(file_data.cFileName, "..")) {
                found = true;
                goto cleanup;
            }
        } while (0 != FindNextFile(file, &file_data));
    }
  cleanup:
    FindClose(file);
    return found;
#endif
}
