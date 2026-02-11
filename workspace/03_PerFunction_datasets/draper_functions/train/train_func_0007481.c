check_is_dir(char *dstfname)
{
    struct sftp_packet *pktin;
    struct sftp_request *req, *rreq;
    struct fxp_attrs attrs;
    int result;

    sftp_register(req = fxp_stat_send(dstfname));
    rreq = sftp_find_request(pktin = sftp_recv());
    compare_req_rreq(req, rreq);
    result = fxp_stat_recv(pktin, rreq, &attrs);

    if (result &&
	(attrs.flags & SSH_FILEXFER_ATTR_PERMISSIONS) &&
	(attrs.permissions & 0040000))
	return TRUE;
    else
	return FALSE;
}
