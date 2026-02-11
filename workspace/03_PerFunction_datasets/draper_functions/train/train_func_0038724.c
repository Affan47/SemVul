cl_set_corerootdir(const char * dir)
{
	if (dir == NULL || *dir != '/') {
		cl_perror("Invalid dir in cl_set_corerootdir() [%s]"
		,	dir ? dir : "<NULL>");
		errno = EINVAL;
		return -1;
	}
	if (coreroot != NULL) {
		free(coreroot);
		coreroot = NULL;
	}
	coreroot = strdup(dir);
	if (coreroot == NULL) {
		return -1;
	}
	return 0;
}
