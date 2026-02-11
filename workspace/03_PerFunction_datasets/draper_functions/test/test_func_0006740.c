sftp_cmd_cd(struct sftp_command *cmd)
{
    struct fxp_handle *dirh;
    struct sftp_packet *pktin;
    struct sftp_request *req, *rreq;
    char *dir;

    if (back == NULL) {
	not_connected();
	return 0;
    }

    if (cmd->nwords < 2)
	dir = dupstr(homedir);
    else
	dir = canonify(cmd->words[1], 0);

    if (!dir) {
	fzprintf(sftpError, "%s: canonify: %s", dir, fxp_error());
	return 0;
    }

    sftp_register(req = fxp_opendir_send(dir));
    rreq = sftp_find_request(pktin = sftp_recv());
    compare_req_rreq(req, rreq);
    dirh = fxp_opendir_recv(pktin, rreq);

    if (!dirh) {
	fzprintf(sftpError, "Directory %s: %s\n", dir, fxp_error());
	sfree(dir);
	return 0;
    }

    sftp_register(req = fxp_close_send(dirh));
    rreq = sftp_find_request(pktin = sftp_recv());
    compare_req_rreq(req, rreq);
    fxp_close_recv(pktin, rreq);

    sfree(pwd);
    pwd = dir;
    fzprintf(sftpReply, "New directory is: \"%s\"", pwd);

    return 1;
}
