nfs3_readdir (rpcsvc_request_t *req, struct nfs3_fh *fh, cookie3 cookie,
              uint64_t cverf, count3 dircount, count3 maxcount)
{
        xlator_t                *vol = NULL;
        nfsstat3                stat = NFS3ERR_SERVERFAULT;
        int                     ret = -EFAULT;
        struct nfs3_state       *nfs3 = NULL;
        nfs3_call_state_t       *cs = NULL;

        if ((!req) || (!fh)) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Bad arguments");
                return -1;
        }

        nfs3_log_readdir_call (rpcsvc_request_xid (req), fh, dircount,
                               maxcount);
        nfs3_validate_gluster_fh (fh, stat, nfs3err);
        nfs3_validate_nfs3_state (req, nfs3, stat, nfs3err, ret);
        nfs3_map_fh_to_volume (nfs3, fh, req, vol, stat, nfs3err);
        nfs3_volume_started_check (nfs3, vol, ret, out);
        nfs3_handle_call_state_init (nfs3, cs, req, vol, stat, nfs3err);

        cs->cookieverf = cverf;
        cs->dircount = dircount;
        cs->maxcount = maxcount;
        cs->cookie = cookie;
        cs->parent = *fh;
        ret = nfs3_fh_resolve_and_resume (cs, fh, NULL,
                                          nfs3_readdir_open_resume);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                if (maxcount == 0) {
                        nfs3_log_common_res (rpcsvc_request_xid (req),
                                             NFS3_READDIR, stat, -ret);
                        nfs3_readdir_reply (req, stat, NULL, 0, NULL, NULL, 0,
                                            0);
                } else {
                        nfs3_log_common_res (rpcsvc_request_xid (req),
                                             NFS3_READDIRP, stat, -ret);
                        nfs3_readdirp_reply (req, stat, NULL, 0, NULL, NULL, 0,
                                             0, 0);
                }


                ret = 0;
                nfs3_call_state_wipe (cs);
        }
out:
        return ret;
}
