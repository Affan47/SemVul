dht_truncate_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int op_ret, int op_errno, struct iatt *prebuf,
                  struct iatt *postbuf, dict_t *xdata)
{
        dht_local_t  *local = NULL;
        call_frame_t *prev = NULL;
        int           ret = -1;

        GF_VALIDATE_OR_GOTO ("dht", frame, err);
        GF_VALIDATE_OR_GOTO ("dht", this, out);
        GF_VALIDATE_OR_GOTO ("dht", frame->local, out);
        GF_VALIDATE_OR_GOTO ("dht", cookie, out);

        local = frame->local;
        prev = cookie;

        if ((op_ret == -1) && (op_errno != ENOENT)) {
                local->op_errno = op_errno;
                local->op_ret = -1;
                gf_log (this->name, GF_LOG_DEBUG,
                        "subvolume %s returned -1 (%s)",
                        prev->this->name, strerror (op_errno));

                goto out;
        }

        if (local->call_cnt != 1) {
                if (local->stbuf.ia_blocks) {
                        dht_iatt_merge (this, postbuf, &local->stbuf, NULL);
                        dht_iatt_merge (this, prebuf, &local->prebuf, NULL);
                }
                goto out;
        }

        local->rebalance.target_op_fn = dht_truncate2;

        local->op_errno = op_errno;

        if ((op_ret == -1) || IS_DHT_MIGRATION_PHASE2 (postbuf)) {
                ret = dht_rebalance_complete_check (this, frame);
                if (!ret)
                        return 0;
        }


        if (IS_DHT_MIGRATION_PHASE1 (postbuf)) {
                dht_iatt_merge (this, &local->stbuf, postbuf, NULL);
                dht_iatt_merge (this, &local->prebuf, prebuf, NULL);
                ret = fd_ctx_get (local->fd, this, NULL);
                if (!ret || !local->fd) {
                        dht_truncate2 (this, frame, 0);
                        return 0;
                }
                ret = dht_rebalance_in_progress_check (this, frame);
                if (!ret)
                        return 0;
        }

out:
        DHT_STRIP_PHASE1_FLAGS (postbuf);
        DHT_STRIP_PHASE1_FLAGS (prebuf);
        DHT_STACK_UNWIND (truncate, frame, op_ret, op_errno,
                          prebuf, postbuf, xdata);
err:
        return 0;
}
