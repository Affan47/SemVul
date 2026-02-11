sftp_begin_wildcard_matching(char *name)
{
    struct sftp_packet *pktin;
    struct sftp_request *req, *rreq;
    char *wildcard;
    char *unwcdir, *tmpdir, *cdir;
    int len, check;
    SftpWildcardMatcher *swcm;
    struct fxp_handle *dirh;


    wildcard = stripslashes(name, 0);

    unwcdir = dupstr(name);
    len = wildcard - name;
    unwcdir[len] = '\0';
    if (len > 0 && unwcdir[len-1] == '/')
	unwcdir[len-1] = '\0';
    tmpdir = snewn(1 + len, char);
    check = wc_unescape(tmpdir, unwcdir);
    sfree(tmpdir);

    if (!check) {
	fzprintf(sftpError, "Multiple-level wildcards are not supported");
	sfree(unwcdir);
	return NULL;
    }

    cdir = canonify(unwcdir, 0);

    sftp_register(req = fxp_opendir_send(cdir));
    rreq = sftp_find_request(pktin = sftp_recv());
    compare_req_rreq(req, rreq);
    dirh = fxp_opendir_recv(pktin, rreq);

    if (dirh) {
	swcm = snew(SftpWildcardMatcher);
	swcm->dirh = dirh;
	swcm->names = NULL;
	swcm->wildcard = dupstr(wildcard);
	swcm->prefix = unwcdir;
    } else {
	fzprintf(sftpError, "Unable to open %s: %s", cdir, fxp_error());
	swcm = NULL;
	sfree(unwcdir);
    }

    sfree(cdir);

    return swcm;
}
