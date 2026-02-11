opal_os_dirpath_is_empty(const char *path ) {
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
}
