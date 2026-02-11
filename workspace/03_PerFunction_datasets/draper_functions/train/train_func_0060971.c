sftp_finish_wildcard_matching(SftpWildcardMatcher *swcm)
{
    struct sftp_packet *pktin;
    struct sftp_request *req, *rreq;

    sftp_register(req = fxp_close_send(swcm->dirh));
    rreq = sftp_find_request(pktin = sftp_recv());
    compare_req_rreq(req, rreq);
    fxp_close_recv(pktin, rreq);

    if (swcm->names)
	fxp_free_names(swcm->names);

    sfree(swcm->prefix);
    sfree(swcm->wildcard);

    sfree(swcm);
}
