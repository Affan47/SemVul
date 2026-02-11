nfs3_rename (rpcsvc_request_t *req, struct nfs3_fh *olddirfh, char *oldname,
             struct nfs3_fh *newdirfh, char *newname)
{
        xlator_t                        *vol = NULL;
        nfsstat3                        stat = NFS3ERR_SERVERFAULT;
        int                             ret = -EFAULT;
        struct nfs3_state               *nfs3 = NULL;
        nfs3_call_state_t               *cs = NULL;

        if ((!req) || (!olddirfh) || (!oldname) || (!newdirfh) || (!newname)) {
                gf_log (GF_NFS3, GF_LOG_ERROR, "Bad arguments");
                return -1;
        }

        nfs3_log_rename_call (rpcsvc_request_xid (req), olddirfh, oldname,
                              newdirfh, newname);
        nfs3_validate_gluster_fh (olddirfh, stat, nfs3err);
        nfs3_validate_gluster_fh (newdirfh, stat, nfs3err);
        nfs3_validate_nfs3_state (req, nfs3, stat, nfs3err, ret);
        nfs3_validate_strlen_or_goto(oldname, NFS_NAME_MAX, nfs3err, stat, ret);
        nfs3_validate_strlen_or_goto(newname, NFS_NAME_MAX, nfs3err, stat, ret);
        nfs3_map_fh_to_volume (nfs3, olddirfh, req, vol, stat, nfs3err);
        nfs3_volume_started_check (nfs3, vol, ret, out);
        nfs3_check_rw_volaccess (nfs3, olddirfh->exportid, stat, nfs3err);
        nfs3_handle_call_state_init (nfs3, cs, req, vol, stat, nfs3err);


        cs->fh = *newdirfh;
        cs->pathname = gf_strdup (newname);
        if (!cs->pathname) {
                stat = NFS3ERR_SERVERFAULT;
                ret = -1;
                goto nfs3err;
        }

        ret = nfs3_fh_resolve_and_resume (cs, olddirfh, oldname,
                                          nfs3_rename_resume_src);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

nfs3err:
        if (ret < 0) {
                nfs3_log_common_res (rpcsvc_request_xid (req), NFS3_RENAME,
                                     stat, -ret);
                nfs3_rename_reply (req, stat, NULL, NULL, NULL, NULL, NULL);
                nfs3_call_state_wipe (cs);


                ret = 0;
        }
out:
        return ret;
}
