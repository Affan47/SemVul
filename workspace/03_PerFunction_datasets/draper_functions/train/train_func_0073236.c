afr_unlock_lower_entrylk (call_frame_t *frame, xlator_t *this)
{
        afr_internal_lock_t *int_lock = NULL;
        afr_local_t         *local    = NULL;
        afr_private_t       *priv     = NULL;
        const char          *basename = NULL;
        loc_t               *loc      = NULL;
        int call_count = 0;
        int i = -1;

        local = frame->local;
        int_lock = &local->internal_lock;
        priv  = this->private;

        basename = int_lock->lk_basename;
        if (int_lock->lk_loc)
                loc = int_lock->lk_loc;

        call_count = __is_lower_locked (frame, this);
        int_lock->lk_call_count = call_count;

        if (!call_count){
                gf_log (this->name, GF_LOG_TRACE,
                        "No internal locks unlocked");
                int_lock->lock_cbk (frame, this);
                goto out;
        }

        for (i = 0; i < priv->child_count; i++) {
                if (int_lock->lower_locked_nodes[i] & LOCKED_LOWER) {
                        afr_trace_entrylk_in (frame, AFR_ENTRYLK_NB_TRANSACTION,
                                              AFR_UNLOCK_OP, basename, i);

                        STACK_WIND_COOKIE (frame, afr_unlock_entrylk_cbk,
                                           (void *) (long) i,
                                           priv->children[i],
                                           priv->children[i]->fops->entrylk,
                                           this->name,
                                           loc, basename,
                                           ENTRYLK_UNLOCK, ENTRYLK_WRLCK);

                        if (!--call_count)
                                break;

                }
        }

out:
        return 0;

}
