nfs3_commit_resume (void *carg)
{
        nfsstat3                stat = NFS3ERR_SERVERFAULT;
        int                     ret = -EFAULT;
        nfs_user_t              nfu = {0, };
        nfs3_call_state_t       *cs = NULL;

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nfs3_check_fh_resolve_status (cs, stat, nfs3err);

        if (nfs3_export_sync_trusted (cs->nfs3state, cs->resolvefh.exportid)) {
                ret = -1;
                stat = NFS3_OK;
                goto nfs3err;
        }

        nfs_request_user_init (&nfu, cs->req);
        ret = nfs_flush (cs->nfsx, cs->vol, &nfu, cs->fd,
                         nfs3svc_commit_cbk, cs);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (cs->req), NFS3_COMMIT,
                                     stat, -ret);
                nfs3_commit_reply (cs->req, stat, cs->nfs3state->serverstart,
                                   NULL, NULL);
                nfs3_call_state_wipe (cs);
                ret = 0;
        }

        return 0;
}
