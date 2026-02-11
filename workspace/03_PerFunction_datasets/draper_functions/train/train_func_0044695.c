fxp_realpath_recv(struct sftp_packet *pktin, struct sftp_request *req)
{
    sfree(req);

    if (pktin->type == SSH_FXP_NAME) {
	unsigned long count;
	char *path;
	int len;

	if (!sftp_pkt_getuint32(pktin, &count) || count != 1) {
	    fxp_internal_error("REALPATH did not return name count of 1");
            sftp_pkt_free(pktin);
	    return NULL;
	}
	if (!sftp_pkt_getstring(pktin, &path, &len)) {
	    fxp_internal_error("REALPATH returned malformed FXP_NAME");
            sftp_pkt_free(pktin);
	    return NULL;
	}
	path = mkstr(path, len);
	sftp_pkt_free(pktin);
	return path;
    } else {
	fxp_got_status(pktin);
        sftp_pkt_free(pktin);
	return NULL;
    }
}
