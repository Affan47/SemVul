dht_lk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
            int op_ret, int op_errno, struct gf_flock *flock, dict_t *xdata)
{
        DHT_STACK_UNWIND (lk, frame, op_ret, op_errno, flock, xdata);

        return 0;
}
