pkgcdb_load(char *dbfile, int str_margin, int pathnode_margin)
{
    int fd;
    char buf[8];
    PathNodeTree pnt;
    StrTable st;

    if (dbfile == NULL)
	return NULL;
    fd = open(dbfile, O_RDONLY);
    if (fd < 0) {
	return NULL;
    }
    if (read(fd, buf, sizeof(buf)) < 0) {
	return NULL;
    }
    if (strncmp(buf, PKGCDB_VERSION_TAG, sizeof(buf)) != 0) {
	MSG(("magic mismatch: %8s\n", buf));
	return NULL;
    }
    DPRINT(("fd=%d magic: %8s\n", fd, buf));
    st = strtab_restore(fd, str_margin);
    if (st == NULL) {
	MSG(("strtab read error\n"));
	close(fd);
	return NULL;
    }
    pnt = pathnode_restore(fd, st, pathnode_margin);
    if (pnt == NULL) {
	MSG(("pathnode read error\n"));
	close(fd);
	return NULL;
    }
    close(fd);
    return pnt;
}
