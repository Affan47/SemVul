nfs3_readlink (rpcsvc_request_t *req, struct nfs3_fh *fh)
{
        xlator_t                        *vol = NULL;
        nfsstat3                        stat = NFS3ERR_SERVERFAULT;
        int                             ret = -EFAULT;
        struct nfs3_state               *nfs3 = NULL;
        nfs3_call_state_t               *cs = NULL;

        if ((!req) || (!fh)) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Bad arguments");
                return -1;
        }

        nfs3_log_common_call (rpcsvc_request_xid (req), "READLINK", fh);
        nfs3_validate_gluster_fh (fh, stat, nfs3err);
        nfs3_validate_nfs3_state (req, nfs3, stat, nfs3err, ret);
        nfs3_map_fh_to_volume (nfs3, fh, req, vol, stat, nfs3err);
        nfs3_volume_started_check (nfs3, vol, ret, out);
        nfs3_handle_call_state_init (nfs3, cs, req, vol, stat, nfs3err);

        ret = nfs3_fh_resolve_and_resume (cs, fh, NULL, nfs3_readlink_resume);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (req), "READLINK",
                                     stat, -ret);
                nfs3_readlink_reply (req, stat, NULL, NULL);
                nfs3_call_state_wipe (cs);


                ret = 0;
        }
out:
        return ret;
}
