cfg_mkdir(char *filename)
{
    char *h;
    int rc;

    h = strrchr(filename,'/');
    if (!h  ||  h == filename)
	return -1;
    *h = '\0';
    rc = mkdir(filename,0777);
    if (-1 == rc && ENOENT == errno) {
	cfg_mkdir(filename);
	rc = mkdir(filename,0777);
    }
    if (-1 == rc)
	fprintf(stderr,"mkdir(%s): %s\n",filename,strerror(errno));
    *h = '/';
    return rc;
}
