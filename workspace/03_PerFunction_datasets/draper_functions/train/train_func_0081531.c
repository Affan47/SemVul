dht_rmdir_readdirp_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                        int op_ret, int op_errno, gf_dirent_t *entries,
                        dict_t *xdata)
{
        dht_local_t  *local = NULL;
        int           this_call_cnt = -1;
        call_frame_t *prev = NULL;
        xlator_t     *src = NULL;
        int           ret = 0;

        local = frame->local;
        prev  = cookie;
        src   = prev->this;

        if (op_ret > 2) {
                ret = dht_rmdir_is_subvol_empty (frame, this, entries, src);

                switch (ret) {
                case 0:
                        gf_log (this->name, GF_LOG_TRACE,
                                "readdir on %s for %s returned %d entries",
                                prev->this->name, local->loc.path, op_ret);
                        local->op_ret = -1;
                        local->op_errno = ENOTEMPTY;
                        break;
                default:

                        gf_log (this->name, GF_LOG_TRACE,
                                "readdir on %s for %s found %d linkfiles",
                                prev->this->name, local->loc.path, ret);
                        break;
                }
        }

        this_call_cnt = dht_frame_return (frame);

        if (is_last_call (this_call_cnt)) {
                dht_rmdir_do (frame, this);
        }

        return 0;
}
