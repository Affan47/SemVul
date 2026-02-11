dht_ufo_xattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int op_ret, int op_errno, dict_t *xdata)
{
        dht_local_t  *local = NULL;
        int           this_call_cnt = 0;
        call_frame_t *prev = NULL;

        local = frame->local;
        prev = cookie;

        LOCK (&frame->lock);
        {
                if (op_ret == -1) {
                        local->op_ret = -1;
                        local->op_errno = op_errno;
                        gf_log (this->name, GF_LOG_DEBUG,
                                "subvolume %s returned -1 (%s)",
                                prev->this->name, strerror (op_errno));
                        goto unlock;
                }
        }
unlock:
        UNLOCK (&frame->lock);

        this_call_cnt = dht_frame_return (frame);
        if (is_last_call (this_call_cnt)) {
                DHT_STACK_UNWIND (setxattr, frame, local->op_ret,
                                  local->op_errno, NULL);
        }

        return 0;
}
