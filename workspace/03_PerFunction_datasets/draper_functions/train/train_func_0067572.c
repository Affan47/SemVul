nfs3_readdir_read_resume (void *carg)
{
        nfsstat3                stat = NFS3ERR_SERVERFAULT;
        int                     ret = -EFAULT;
        nfs3_call_state_t       *cs = NULL;
        struct nfs3_state       *nfs3 = NULL;

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nfs3_check_fh_resolve_status (cs, stat, nfs3err);
        nfs3 = rpcsvc_request_program_private (cs->req);
        ret = nfs3_verify_dircookie (nfs3, cs->fd, cs->cookie, cs->cookieverf,
                                     &stat);
        if (ret < 0)
                goto nfs3err;

        ret = nfs3_readdir_process (cs);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);
nfs3err:
        if (ret < 0) {
                if (cs->maxcount == 0) {
                        nfs3_log_common_res (rpcsvc_request_xid (cs->req),
                                             "READDIR", stat, -ret);
                        nfs3_readdir_reply (cs->req, stat, NULL, 0, NULL, NULL,
                                            0, 0);
                } else {
                        nfs3_log_common_res (rpcsvc_request_xid (cs->req),
                                             "READDIRP", stat, -ret);
                        nfs3_readdirp_reply (cs->req, stat, NULL, 0, NULL, NULL,
                                             0, 0, 0);
                }
                nfs3_call_state_wipe (cs);
        }

        return 0;
}
