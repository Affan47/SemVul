G__make_mapset_element(const char *p_element)
{
    char path[GPATH_MAX];
    char *p;
    const char *element;

    element = p_element;
    if (*element == 0)
	return 0;

    G__file_name(p = path, "", "", G_mapset());
    while (*p)
	p++;

    --p;
    if (*p++ != '/') {
	*p++ = '/';
	*p = 0;
    }


    while (1) {
	if (*element == '/' || *element == 0) {
	    *p = 0;
	    if (access(path, 0) != 0) {
		if (G_mkdir(path) != 0)
		    G_fatal_error(_("Unable to make mapset element %s (%s): %s"),
				  p_element, path, strerror(errno));
	    }
	    if (access(path, 0) != 0)
		G_fatal_error(_("Unable to access mapset element %s (%s): %s"),
			      p_element, path, strerror(errno));
	    if (*element == 0)
		return 1;
	}
	*p++ = *element++;
    }
}
