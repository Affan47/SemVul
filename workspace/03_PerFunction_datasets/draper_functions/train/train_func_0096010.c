do_sftp_init(void)
{
    struct sftp_packet *pktin;
    struct sftp_request *req, *rreq;


    if (!fxp_init()) {
	fzprintf(sftpError,
		"Fatal: unable to initialise SFTP on server: %s\n", fxp_error());
	return 1;
    }


    sftp_register(req = fxp_realpath_send("."));
    rreq = sftp_find_request(pktin = sftp_recv());
    compare_req_rreq(req, rreq);
    homedir = fxp_realpath_recv(pktin, rreq);

    if (!homedir) {
	fzprintf(sftpError,
		"Warning: failed to resolve home directory: %s\n",
		fxp_error());
	homedir = dupstr(".");
    }
    pwd = dupstr(homedir);
    return 0;
}
