mnt3svc_mnt (rpcsvc_request_t *req)
{
        struct iovec            pvec = {0, };
        char                    path[MNTPATHLEN];
        int                     ret = -1;
        struct mount3_state     *ms = NULL;
        mountstat3              mntstat = MNT3ERR_SERVERFAULT;
        struct mnt3_export      *exp = NULL;
        struct nfs_state        *nfs = NULL;

        if (!req)
                return -1;

        pvec.iov_base = path;
        pvec.iov_len = MNTPATHLEN;
        ret = xdr_to_mountpath (pvec, req->msg[0]);
        if (ret == -1) {
                gf_log (GF_MNT, GF_LOG_ERROR, "Failed to decode args");
                rpcsvc_request_seterr (req, GARBAGE_ARGS);
                goto rpcerr;
        }

        ms = (struct mount3_state *)rpcsvc_request_program_private (req);
        if (!ms) {
                gf_log (GF_MNT, GF_LOG_ERROR, "Mount state not present");
                rpcsvc_request_seterr (req, SYSTEM_ERR);
                ret = -1;
                goto rpcerr;
        }

        ret = 0;
        nfs = (struct nfs_state *)ms->nfsx->private;
        gf_log (GF_MNT, GF_LOG_DEBUG, "dirpath: %s", path);
        ret = mnt3_find_export (req, path, &exp);
        if (ret == -2) {
                ret = 0;
                goto rpcerr;
        } else if (ret < 0) {
                ret = -1;
                mntstat = MNT3ERR_NOENT;
                goto mnterr;
        }

        if (!nfs_subvolume_started (nfs, exp->vol)) {
                gf_log (GF_MNT, GF_LOG_DEBUG, "Volume %s not started",
                        exp->vol->name);
                ret = -1;
                mntstat = MNT3ERR_NOENT;
                goto mnterr;
        }

        ret = mnt3_check_client_net (ms, req, exp->vol);
        if (ret == RPCSVC_AUTH_REJECT) {
                mntstat = MNT3ERR_ACCES;
                gf_log (GF_MNT, GF_LOG_DEBUG, "Client mount not allowed");
                ret = -1;
                goto mnterr;
        }

        ret = mnt3svc_mount (req, ms, exp);
        if (ret < 0)
                mntstat = mnt3svc_errno_to_mnterr (-ret);
mnterr:
        if (ret < 0) {
                mnt3svc_mnt_error_reply (req, mntstat);
                ret = 0;
        }

rpcerr:
        return ret;
}
