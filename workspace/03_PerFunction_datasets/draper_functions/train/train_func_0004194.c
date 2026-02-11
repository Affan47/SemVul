_file_read_uint32s(char* file_path, uint32_t** pvalues, int* pnb)
{
	int rc;
	int fd;

	size_t fsize;
	char* buf;
	char* p;

	uint32_t* pa=NULL;
	int i;


	if (pvalues == NULL || pnb == NULL)
		return XCGROUP_ERROR;


	fd = open(file_path, O_RDONLY, 0700);
	if (fd < 0) {
		debug2("unable to open '%s' for reading : %m", file_path);
		return XCGROUP_ERROR;
	}


	fsize=_file_getsize(fd);
	if (fsize == -1) {
		close(fd);
		return XCGROUP_ERROR;
	}


	buf = (char*) xmalloc((fsize+1)*sizeof(char));
	do {
		rc = read(fd, buf, fsize);
	}
	while (rc < 0 && errno == EINTR);
	close(fd);
	buf[fsize]='\0';


	i=0;
	if (rc > 0) {
		p = buf;
		while (index(p, '\n') != NULL) {
			i++;
			p = index(p, '\n') + 1;
		}
	}


	if (i > 0) {
		pa = (uint32_t*) xmalloc(sizeof(uint32_t) * i);
		p = buf;
		i = 0;
		while (index(p, '\n') != NULL) {
			sscanf(p, "%u", pa+i);
			p = index(p, '\n') + 1;
			i++;
		}
	}


	xfree(buf);


	*pvalues = pa;
	*pnb = i;

	return XCGROUP_SUCCESS;
}
