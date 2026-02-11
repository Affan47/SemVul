dht_access_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int op_ret, int op_errno, dict_t *xdata)
{
        int          ret = -1;
        dht_local_t *local = NULL;

        local = frame->local;

        if (local->call_cnt != 1)
                goto out;

        if ((op_ret == -1) && (op_errno == ENOENT)) {

                local->rebalance.target_op_fn = dht_access2;
                ret = dht_rebalance_complete_check (frame->this, frame);
                if (!ret)
                        return 0;
        }

out:
        DHT_STACK_UNWIND (access, frame, op_ret, op_errno, xdata);
        return 0;
}
