opal_os_path(bool relative, ...)
{
    va_list ap;
    char *element, *path;
    size_t num_elements, total_length;

    va_start(ap, relative);


    num_elements = 0;
    total_length = 0;
    while (NULL != (element = va_arg(ap, char*))) {
        num_elements++;
        total_length = total_length + strlen(element);
        if( path_sep[0] != element[0] ) total_length++;
    }
    va_end(ap);

    if (0 == num_elements) {
    	path = (char *)malloc(3);
        path[0] = '\0';
    	if (relative) {
    	    strcpy(path, ".");
            strcat(path, path_sep);
    	} else {
    	    strcpy(path, path_sep);
    	}
    	return(path);
    }


    total_length = total_length + num_elements * strlen(path_sep) + 1;
    if(relative) {
        total_length++;
    }

    if (total_length > OPAL_PATH_MAX) {
    	return(NULL);
    }

    path = (char *)malloc(total_length);
    if (NULL == path) {
        return(NULL);
    }
    path[0] = 0;

    if (relative) {
        strcpy(path, ".");
    }

    va_start(ap, relative);
    if( NULL != (element = va_arg(ap, char*)) ) {
    	if (path_sep[0] != element[0]) {
            strcat(path, path_sep);
        }
        strcat(path, element);
    }
    while (NULL != (element=va_arg(ap, char*))) {
    	if (path_sep[0] != element[0]) {
            strcat(path, path_sep);
        }
        strcat(path, element);
    }

    va_end(ap);
    return opal_make_filename_os_friendly(path);
}
