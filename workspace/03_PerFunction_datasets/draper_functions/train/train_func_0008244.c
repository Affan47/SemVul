dht_selfheal_dir_xattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                            int op_ret, int op_errno, dict_t *xdata)
{
        dht_local_t  *local = NULL;
        call_frame_t *prev = NULL;
        xlator_t     *subvol = NULL;
        int           i = 0;
        dht_layout_t *layout = NULL;
        int           err = 0;
        int           this_call_cnt = 0;

        local = frame->local;
        layout = local->selfheal.layout;
        prev = cookie;
        subvol = prev->this;

        if (op_ret == 0)
                err = 0;
        else
                err = op_errno;

        for (i = 0; i < layout->cnt; i++) {
                if (layout->list[i].xlator == subvol) {
                        layout->list[i].err = err;
                        break;
                }
        }

        this_call_cnt = dht_frame_return (frame);

        if (is_last_call (this_call_cnt)) {
                dht_selfheal_dir_finish (frame, this, 0);
        }

        return 0;
}
