dht_fsyncdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int op_ret, int op_errno, dict_t *xdata)
{
        dht_local_t  *local = NULL;
        int           this_call_cnt = 0;


        local = frame->local;

        LOCK (&frame->lock);
        {
                if (op_ret == -1)
                        local->op_errno = op_errno;

                if (op_ret == 0)
                        local->op_ret = 0;
        }
        UNLOCK (&frame->lock);

        this_call_cnt = dht_frame_return (frame);
        if (is_last_call (this_call_cnt))
                DHT_STACK_UNWIND (fsyncdir, frame, local->op_ret,
                                  local->op_errno, xdata);

        return 0;
}
