nfs3_link_resume_tgt (void *carg)
{
        nfsstat3                stat = NFS3ERR_SERVERFAULT;
        int                     ret = -EFAULT;
        nfs3_call_state_t       *cs = NULL;

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nfs3_check_fh_resolve_status (cs, stat, nfs3err);
        nfs_loc_copy (&cs->oploc, &cs->resolvedloc);
        nfs_loc_wipe (&cs->resolvedloc);

        ret = nfs3_fh_resolve_and_resume (cs, &cs->fh, cs->pathname,
                                          nfs3_link_resume_lnk);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (cs->req), NFS3_LINK,
                                     stat, -ret);
                nfs3_link_reply (cs->req, stat, NULL, NULL, NULL);
                nfs3_call_state_wipe (cs);
        }

        return ret;
}
