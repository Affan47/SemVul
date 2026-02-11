nfs3svc_readlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, const char *path,
                      struct iatt *buf, dict_t *xdata)
{
        nfsstat3                stat = NFS3ERR_SERVERFAULT;
        nfs3_call_state_t       *cs = NULL;

        cs = frame->local;
        if (op_ret == -1) {
                gf_log (GF_NFS, GF_LOG_WARNING,
                        "%x: %s => -1 (%s)", rpcsvc_request_xid (cs->req),
                        cs->resolvedloc.path, strerror (op_errno));
                stat = nfs3_errno_to_nfsstat3 (op_errno);
                goto nfs3err;
        }

        stat = NFS3_OK;

nfs3err:
        nfs3_log_readlink_res (rpcsvc_request_xid (cs->req), stat, op_errno,
                               (char *)path);
        nfs3_readlink_reply (cs->req, stat, (char *)path, buf);
        nfs3_call_state_wipe (cs);

        return 0;
}
