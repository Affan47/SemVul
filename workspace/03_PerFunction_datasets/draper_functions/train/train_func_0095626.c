dht_attr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
              int op_ret, int op_errno, struct iatt *stbuf)
{
        dht_local_t  *local = NULL;
        int           this_call_cnt = 0;
        call_frame_t *prev = NULL;

        GF_VALIDATE_OR_GOTO ("dht", frame, err);
        GF_VALIDATE_OR_GOTO ("dht", this, out);
        GF_VALIDATE_OR_GOTO ("dht", frame->local, out);
        GF_VALIDATE_OR_GOTO ("dht", cookie, out);

        local = frame->local;
        prev = cookie;

        LOCK (&frame->lock);
        {
                if (op_ret == -1) {
                        local->op_errno = op_errno;
                        gf_log (this->name, GF_LOG_DEBUG,
                                "subvolume %s returned -1 (%s)",
                                prev->this->name, strerror (op_errno));

                        goto unlock;
                }

                dht_iatt_merge (this, &local->stbuf, stbuf, prev->this);

                local->op_ret = 0;
        }
unlock:
        UNLOCK (&frame->lock);
out:
        this_call_cnt = dht_frame_return (frame);
        if (is_last_call (this_call_cnt)) {
                DHT_STACK_UNWIND (stat, frame, local->op_ret, local->op_errno,
                                  &local->stbuf);
        }
err:
        return 0;
}
