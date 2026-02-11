dht_lookup_unlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int op_ret, int op_errno,
                       struct iatt *preparent, struct iatt *postparent)
{
        int  this_call_cnt = 0;

        this_call_cnt = dht_frame_return (frame);
        if (is_last_call (this_call_cnt)) {
                dht_lookup_everywhere_done (frame, this);
        }

        return 0;
}
