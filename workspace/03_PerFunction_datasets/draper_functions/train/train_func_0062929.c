nlm4_unlock_resume (void *carg)
{
        nlm4_stats                      stat = nlm4_failed;
        int                             ret = -1;
        nfs3_call_state_t               *cs = NULL;
        nlm_client_t                    *nlmclnt = NULL;

        if (!carg)
                return ret;

        cs = (nfs3_call_state_t *)carg;
        nlm4_check_fh_resolve_status (cs, stat, nlm4err);

        nlmclnt = nlm_get_uniq (cs->args.nlm4_unlockargs.alock.caller_name);
        if (nlmclnt == NULL) {
                stat = nlm4_granted;
                gf_log (GF_NLM, GF_LOG_WARNING, "nlm_get_uniq() returned NULL");
                goto nlm4err;
        }
        cs->fd = fd_lookup_uint64 (cs->resolvedloc.inode, (uint64_t)nlmclnt);
        if (cs->fd == NULL) {
                stat = nlm4_granted;
                gf_log (GF_NLM, GF_LOG_WARNING, "fd_lookup_uint64() returned "
                        "NULL");
                goto nlm4err;
        }
        ret = nlm4_unlock_fd_resume (cs);

nlm4err:
        if (ret < 0) {
                gf_log (GF_NLM, GF_LOG_WARNING, "unable to unlock_fd_resume");
                stat = nlm4_errno_to_nlm4stat (-ret);
                nlm4_generic_reply (cs->req, cs->args.nlm4_unlockargs.cookie,
                                    stat);

                nfs3_call_state_wipe (cs);
        }

        return 0;
}
