afr_trace_entrylk_in (call_frame_t *frame, xlator_t *this,
                      afr_lock_call_type_t lock_call_type,
                      afr_lock_op_type_t lk_op_type, const char *basename,
                      int32_t child_index)
{
        afr_local_t         *local    = NULL;
        afr_internal_lock_t *int_lock = NULL;

        char lock[256];
        char lockee[256];
        char lock_call_type_str[256];

        local    = frame->local;
        int_lock = &local->internal_lock;

        afr_print_entrylk (lock, 256, basename, &frame->root->lk_owner);
        afr_print_lockee (lockee, 256, &local->loc, local->fd, child_index);

        afr_set_lock_call_type (lock_call_type, lock_call_type_str, int_lock);

        gf_log (this->name, GF_LOG_INFO,
                "[%s %s] Lock={%s} Lockee={%s} Number={%llu}",
                lock_call_type_str,
                lk_op_type == AFR_LOCK_OP ? "LOCK REQUEST" : "UNLOCK REQUEST",
                lock, lockee,
                (unsigned long long) int_lock->lock_number);
}
