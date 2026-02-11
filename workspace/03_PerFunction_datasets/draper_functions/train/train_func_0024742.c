nlm4svc_lock_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct gf_flock *flock,
                  dict_t *xdata)
{
        nlm4_stats                      stat = nlm4_denied;
        nfs3_call_state_t              *cs = NULL;
        int                             transit_cnt = -1;
        char                            *caller_name = NULL;
        pthread_t thr;

        cs = frame->local;
        caller_name = cs->args.nlm4_lockargs.alock.caller_name;
        transit_cnt = nlm_dec_transit_count (cs->fd,
                                             caller_name);
        if (op_ret == -1) {
                if (transit_cnt == 0)
                        nlm_search_and_delete (cs->fd,
                                               caller_name);
                stat = nlm4_errno_to_nlm4stat (op_errno);
                goto err;
        } else {
                stat = nlm4_granted;
                if (!nlm_monitor (caller_name)) {

                        pthread_create (&thr, NULL, nsm_monitor, (void*)caller_name);
                }
        }

err:
        if (cs->args.nlm4_lockargs.block) {
                cs->frame = copy_frame (frame);
                nlm4svc_send_granted (cs);
        } else {
                nlm4_generic_reply (cs->req, cs->args.nlm4_lockargs.cookie,
                                    stat);
                nfs3_call_state_wipe (cs);
        }
        return 0;
}
