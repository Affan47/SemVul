nlm4_lock_fd_resume (void *carg)
{
        nlm4_stats                      stat = nlm4_denied;
        int                             ret = -EFAULT;
        nfs_user_t                      nfu = {0, };
        nfs3_call_state_t               *cs = NULL;
        struct gf_flock                 flock = {0, };

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nlm4_check_fh_resolve_status (cs, stat, nlm4err);

        (void) nlm_search_and_add (cs->fd,
                                   cs->args.nlm4_lockargs.alock.caller_name);
        nfs_request_user_init (&nfu, cs->req);
        nlm4_lock_to_gf_flock (&flock, &cs->args.nlm4_lockargs.alock,
                               cs->args.nlm4_lockargs.exclusive);
        nlm_copy_lkowner (&nfu.lk_owner, &cs->args.nlm4_lockargs.alock.oh);
        if (cs->args.nlm4_lockargs.block) {
                nlm4_generic_reply (cs->req, cs->args.nlm4_lockargs.cookie,
                                    nlm4_blocked);
                ret = nfs_lk (cs->nfsx, cs->vol, &nfu, cs->fd, F_SETLKW,
                              &flock, nlm4svc_lock_cbk, cs);
        } else
                ret = nfs_lk (cs->nfsx, cs->vol, &nfu, cs->fd, F_SETLK,
                              &flock, nlm4svc_lock_cbk, cs);

        if (ret < 0)
                stat = nlm4_errno_to_nlm4stat (-ret);
nlm4err:
        if (ret < 0) {
                gf_log (GF_NLM, GF_LOG_ERROR, "unable to call lk()");
                nlm4_generic_reply (cs->req, cs->args.nlm4_lockargs.cookie,
                                    stat);
                nfs3_call_state_wipe (cs);
        }

        return ret;
}
