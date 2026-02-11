closeFile(Expr_t * ex, int fd)
{
    int rv;

    if ((0 <= fd) && (fd <= 2)) {
	exerror("closeF: cannot close standard stream %d", fd);
	return -1;
    }
    if (!ex->file[fd]) {
	exerror("closeF: stream %d not open", fd);
	return -1;
    }
    rv = sfclose(ex->file[fd]);
    if (!rv)
	ex->file[fd] = 0;
    return rv;
}
