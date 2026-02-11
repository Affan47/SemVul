nfs3_readlink_resume (void *carg)
{
        nfsstat3                        stat = NFS3ERR_SERVERFAULT;
        int                             ret = -EFAULT;
        nfs3_call_state_t               *cs = NULL;
        nfs_user_t                      nfu = {0, };

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nfs3_check_fh_resolve_status (cs, stat, nfs3err);
        nfs_request_user_init (&nfu, cs->req);
        ret = nfs_readlink (cs->nfsx, cs->vol, &nfu, &cs->resolvedloc,
                            nfs3svc_readlink_cbk, cs);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (cs->req),
                                     NFS3_READLINK, stat, -ret);
                nfs3_readlink_reply (cs->req, stat, NULL, NULL);
                nfs3_call_state_wipe (cs);
        }

        return ret;
}
