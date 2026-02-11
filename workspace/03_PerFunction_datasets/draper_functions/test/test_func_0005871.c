nfs3_setattr (rpcsvc_request_t *req, struct nfs3_fh *fh, sattr3 *sattr,
              sattrguard3 *guard)
{
        xlator_t                        *vol = NULL;
        nfsstat3                        stat = NFS3ERR_SERVERFAULT;
        int                             ret = -EFAULT;
        struct nfs3_state               *nfs3 = NULL;
        nfs3_call_state_t               *cs = NULL;

        GF_VALIDATE_OR_GOTO (GF_NFS3, req, out);
        GF_VALIDATE_OR_GOTO (GF_NFS3, fh, out);
        GF_VALIDATE_OR_GOTO (GF_NFS3, sattr, out);
        GF_VALIDATE_OR_GOTO (GF_NFS3, guard, out);

        nfs3_log_common_call (rpcsvc_request_xid (req), "SETATTR", fh);
        nfs3_validate_gluster_fh (fh, stat, nfs3err);
        nfs3_validate_nfs3_state (req, nfs3, stat, nfs3err, ret);
        nfs3_map_fh_to_volume (nfs3, fh, req, vol, stat, nfs3err);
        nfs3_volume_started_check (nfs3, vol, ret, out);
        nfs3_check_rw_volaccess (nfs3, fh->exportid, stat, nfs3err);
        nfs3_handle_call_state_init (nfs3, cs, req, vol, stat, nfs3err);

        cs->setattr_valid = nfs3_sattr3_to_setattr_valid (sattr, &cs->stbuf,
                                                          NULL);
        if (guard->check) {
                gf_log (GF_NFS3, GF_LOG_TRACE, "Guard check required");
                cs->timestamp = guard->sattrguard3_u.obj_ctime;
                cs->sattrguardcheck = 1;
        } else {
                gf_log (GF_NFS3, GF_LOG_TRACE, "Guard check not required");
                cs->sattrguardcheck = 0;
        }

        if (!cs->setattr_valid) {
                ret = -EINVAL;
                stat = NFS3_OK;
                gf_log (GF_NFS3, GF_LOG_ERROR, "cs->setattr_valid is invalid");
                goto nfs3err;
        }

        ret = nfs3_fh_resolve_and_resume (cs, fh, NULL, nfs3_setattr_resume);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (req), "SETATTR",
                                     stat, -ret);
                nfs3_setattr_reply (req, stat, NULL, NULL);
                nfs3_call_state_wipe (cs);


                ret = 0;
        }
out:
        return ret;
}
