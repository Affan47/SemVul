afr_lock_lower_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, dict_t *xdata)
{
        afr_internal_lock_t *int_lock    = NULL;
        afr_private_t       *priv        = NULL;
        afr_local_t         *local       = NULL;
        loc_t               *lower       = NULL;
        loc_t               *higher      = NULL;
        const char          *higher_name = NULL;
        int child_index = (long) cookie;

        priv     = this->private;
        local    = frame->local;
        int_lock = &local->internal_lock;

        LOCK (&frame->lock);
        {
                if (op_ret == -1) {
                        if (op_errno == ENOSYS) {


                                gf_log (this->name, GF_LOG_ERROR,
                                        "subvolume does not support locking. "
                                        "please load features/locks xlator on server");

                                local->op_ret   = op_ret;
                        }

                        local->op_errno = op_errno;
                }
        }
        UNLOCK (&frame->lock);

        if (op_ret != 0) {
                afr_unlock (frame, this);
                goto out;
        } else {
                int_lock->lower_locked_nodes[child_index] |= LOCKED_LOWER;
                int_lock->lock_count++;
        }


        lower = lower_path (&local->transaction.parent_loc,
                            local->transaction.basename,
                            &local->transaction.new_parent_loc,
                            local->transaction.new_basename);

        higher = (lower == &local->transaction.parent_loc ?
                  &local->transaction.new_parent_loc :
                  &local->transaction.parent_loc);

        higher_name = (higher == &local->transaction.parent_loc ?
                       local->transaction.basename :
                       local->transaction.new_basename);

        AFR_TRACE_ENTRYLK_IN (frame, this, AFR_ENTRYLK_TRANSACTION,
                              AFR_LOCK_OP, higher_name, child_index);


        STACK_WIND_COOKIE (frame, afr_lock_cbk,
                           (void *) (long) child_index,
                           priv->children[child_index],
                           priv->children[child_index]->fops->entrylk,
                           this->name, higher, higher_name,
                           ENTRYLK_LOCK, ENTRYLK_WRLCK, NULL);

out:
        return 0;
}
