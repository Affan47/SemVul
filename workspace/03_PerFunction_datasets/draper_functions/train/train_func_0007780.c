nfs3svc_write_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                   struct iatt *postbuf, dict_t *xdata)
{
        nfsstat3                stat = NFS3ERR_SERVERFAULT;
        int                     ret = -EFAULT;
        nfs_user_t              nfu = {0, };
        nfs3_call_state_t       *cs = NULL;
        struct nfs3_state       *nfs3 = NULL;
        int                     write_trusted = 0;
        int                     sync_trusted = 0;

        cs = frame->local;
        nfs3 = rpcsvc_request_program_private (cs->req);
        if (op_ret == -1) {
                gf_log (GF_NFS, GF_LOG_WARNING,
                        "%x: %s => -1 (%s)", rpcsvc_request_xid (cs->req),
                        cs->resolvedloc.path, strerror (op_errno));
                stat = nfs3_errno_to_nfsstat3 (op_errno);
                goto err;
        }

        stat = NFS3_OK;
        cs->maxcount = op_ret;

        write_trusted = nfs3_export_write_trusted (cs->nfs3state,
                                                   cs->resolvefh.exportid);
        sync_trusted = nfs3_export_sync_trusted (cs->nfs3state,
                                                 cs->resolvefh.exportid);
        ret = nfs3_write_how (&cs->writetype, write_trusted, sync_trusted);
        if (ret == -1)
                goto err;

        nfs_request_user_init (&nfu, cs->req);


        cs->stbuf = *prebuf;
        ret = nfs_fsync (cs->nfsx, cs->vol, &nfu, cs->fd, 0,
                         nfs3svc_write_fsync_cbk, cs);
        if (ret < 0)
                stat = nfs3_errno_to_nfsstat3 (-ret);

err:
        if (ret < 0) {
                nfs3_log_write_res (rpcsvc_request_xid (cs->req), stat,
                                    op_errno, cs->maxcount, cs->writetype,
                                    nfs3->serverstart);
                nfs3_write_reply (cs->req, stat, cs->maxcount,
                                  cs->writetype, nfs3->serverstart, prebuf,
                                  postbuf);
                nfs3_call_state_wipe (cs);
        }

        return 0;
}
