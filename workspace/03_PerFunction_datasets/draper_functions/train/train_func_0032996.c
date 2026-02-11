getPnfsIDbyPath(const char *path)
{

	char           *pnfsLayer;
	int             tmp;
	struct          stat buf;
	char *dir;
	char *file;
	char *pnfsId;

	dir = xdirname(path);
	file = xbasename(path);


	pnfsLayer = (char *) malloc(strlen(file) + strlen("/.(id)()") + 1 + strlen(dir));

	if (pnfsLayer == NULL) {
		dc_errno = DEPNFSID;
		return NULL;
	}

	sprintf(pnfsLayer, "%s%c.(id)(%s)", dir, PATH_SEPARATOR, file);
	free(dir);
	free(file);

	dc_debug(DC_TRACE, "Looking for pnfsID in %s\n", pnfsLayer);
	tmp = system_open(pnfsLayer, O_RDONLY, 0);


	free(pnfsLayer);

	if (tmp < 0) {
		dc_errno = DEPNFSID;
		return NULL;
	}

	if(system_fstat(tmp, &buf) < 0) {
		system_close(tmp);
		dc_errno = DEPNFSID;
		return NULL;

	}


	pnfsId = (char *) malloc(buf.st_size);

	if (pnfsId == NULL) {
		system_close(tmp);
		dc_errno = DEPNFSID;
		return NULL;
	}

	if(system_read(tmp, pnfsId, buf.st_size) != buf.st_size ) {
		system_close(tmp);
		free(pnfsId);
		dc_errno = DEPNFSID;
		return NULL;
	}

	pnfsId[buf.st_size - 1] = '\0';

	system_close(tmp);

	dc_errno = DEOK;
	return pnfsId;
}
