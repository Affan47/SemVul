nfs3svc_mkdir_setattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                           int32_t op_ret, int32_t op_errno,
                           struct iatt *preop, struct iatt *postop)
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
        nfs3_log_newfh_res (rpcsvc_request_xid (cs->req), "MKDIR", stat,
                            op_errno, &cs->fh);
        nfs3_mkdir_reply (cs->req, stat, &cs->fh, postop, &cs->preparent,
                          &cs->postparent);
        nfs3_call_state_wipe (cs);

        return 0;
}
