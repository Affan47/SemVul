afr_trace_inodelk_out (call_frame_t *frame, afr_lock_call_type_t lock_call_type,
                       afr_lock_op_type_t lk_op_type, struct gf_flock *flock,
                       int op_ret, int op_errno, int32_t child_index)
{
        xlator_t            *this     = NULL;
        afr_internal_lock_t *int_lock = NULL;
        afr_local_t         *local    = NULL;
        afr_private_t       *priv     = NULL;

        char lockee[256];
        char lock_call_type_str[256];
        char verdict[16];

        this     = THIS;
        local    = frame->local;
        int_lock = &local->internal_lock;
        priv     = this->private;

        if (!priv->inodelk_trace) {
                return;
        }

        afr_print_lockee (lockee, 256, &local->loc, local->fd, child_index);

        afr_set_lock_call_type (lock_call_type, lock_call_type_str, int_lock);

        afr_print_verdict (op_ret, op_errno, verdict);

        gf_log (this->name, GF_LOG_INFO,
                "[%s %s] [%s] Lockee={%s} Number={%llu}",
                lock_call_type_str,
                lk_op_type == AFR_LOCK_OP ? "LOCK REPLY" : "UNLOCK REPLY",
                verdict,
                lockee,
                (unsigned long long) int_lock->lock_number);

}
