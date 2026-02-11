afr_post_nonblocking_inodelk_cbk (call_frame_t *frame, xlator_t *this)
{
        afr_internal_lock_t *int_lock = NULL;
        afr_local_t         *local    = NULL;

        local    = frame->local;
        int_lock = &local->internal_lock;


        if (int_lock->lock_op_ret < 0) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "Non blocking inodelks failed. Proceeding to blocking");
                int_lock->lock_cbk = afr_post_blocking_inodelk_cbk;
                afr_set_lk_owner (frame, this, frame->root);
                afr_blocking_lock (frame, this);
        } else {

                gf_log (this->name, GF_LOG_DEBUG,
                        "Non blocking inodelks done. Proceeding to FOP");
                afr_internal_lock_finish (frame, this);
        }

        return 0;
}
