acl3_getacl_resume (void *carg)
{
        int                             ret = -1;
        nfs3_call_state_t               *cs = NULL;
        nfsstat3                        stat = NFS3ERR_SERVERFAULT;
        nfs_user_t                      nfu = {0, };

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        acl3_check_fh_resolve_status (cs, stat, acl3err);
        nfs_request_user_init (&nfu, cs->req);

        ret = nfs_stat (cs->nfsx, cs->vol, &nfu, &cs->resolvedloc,
                        acl3_stat_cbk, cs);
        stat = -ret;
acl3err:
        if (ret < 0) {
                gf_log (GF_ACL, GF_LOG_ERROR, "unable to open_and_resume");
                cs->args.getaclreply.status = nfs3_errno_to_nfsstat3 (stat);
                acl3_getacl_reply (cs, &cs->args.getaclreply);
                nfs3_call_state_wipe (cs);
        }

        return ret;
}
