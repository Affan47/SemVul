meth_get_domainkey(struct transaction_t *txn,
			      void *params __attribute__((unused)))
{
    int ret = 0, r, fd = -1, precond;
    const char *path;
    static struct buf pathbuf = BUF_INITIALIZER;
    struct stat sbuf;
    const char *msg_base = NULL;
    unsigned long msg_size = 0;
    struct resp_body_t *resp_body = &txn->resp_body;


    buf_setcstr(&pathbuf, config_dir);
    buf_appendcstr(&pathbuf, txn->req_uri->path);
    path = buf_cstring(&pathbuf);
    r = stat(path, &sbuf);
    if (r || !S_ISREG(sbuf.st_mode)) return HTTP_NOT_FOUND;


    assert(!buf_len(&txn->buf));
    buf_printf(&txn->buf, "%ld-%ld", (long) sbuf.st_mtime, (long) sbuf.st_size);


    txn->flags.ranges = 1;
    precond = check_precond(txn, NULL, buf_cstring(&txn->buf), sbuf.st_mtime);

    switch (precond) {
    case HTTP_OK:
    case HTTP_PARTIAL:
    case HTTP_NOT_MODIFIED:

	resp_body->type = "text/plain";
	resp_body->etag = buf_cstring(&txn->buf);
	resp_body->lastmod = sbuf.st_mtime;
	resp_body->maxage = 86400;
	txn->flags.cc |= CC_MAXAGE | CC_REVALIDATE;
	if (httpd_userid) txn->flags.cc |= CC_PUBLIC;

	if (precond != HTTP_NOT_MODIFIED) break;

    default:

	resp_body->type = NULL;
	return precond;
    }

    if (txn->meth == METH_GET) {

	if ((fd = open(path, O_RDONLY)) == -1) return HTTP_SERVER_ERROR;
	map_refresh(fd, 1, &msg_base, &msg_size, sbuf.st_size, path, NULL);
    }

    write_body(precond, txn, msg_base, sbuf.st_size);

    if (fd != -1) {
	map_free(&msg_base, &msg_size);
	close(fd);
    }

    return ret;
}
