dht_file_setattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int op_ret, int op_errno, struct iatt *prebuf,
                      struct iatt *postbuf)
{
        dht_local_t  *local = NULL;
        call_frame_t *prev = NULL;
        int           ret = -1;

        local = frame->local;
        prev = cookie;

        local->op_errno = op_errno;
        if ((op_ret == -1) && (op_errno != ENOENT)) {
                gf_log (this->name, GF_LOG_DEBUG,
                        "subvolume %s returned -1 (%s)",
                        prev->this->name, strerror (op_errno));
                goto out;
        }

        if (local->call_cnt != 1)
                goto out;

        local->rebalance.target_op_fn = dht_setattr2;


        if ((op_ret == -1) || IS_DHT_MIGRATION_PHASE2 (postbuf)) {
                ret = dht_rebalance_complete_check (this, frame);
                if (!ret)
                        return 0;
        }


out:
        DHT_STRIP_PHASE1_FLAGS (postbuf);
        DHT_STRIP_PHASE1_FLAGS (prebuf);
        DHT_STACK_UNWIND (setattr, frame, op_ret, op_errno,
                          prebuf, postbuf);

        return 0;
}
