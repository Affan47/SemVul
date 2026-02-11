stripe_unlink_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *preparent,
                   struct iatt *postparent, dict_t *xdata)
{
        int32_t         callcnt = 0;
        stripe_local_t *local   = NULL;
        call_frame_t   *prev = NULL;

        if (!this || !frame || !frame->local || !cookie) {
                gf_log ("stripe", GF_LOG_DEBUG, "possible NULL deref");
                goto out;
        }

        prev  = cookie;
        local = frame->local;

        LOCK (&frame->lock);
        {
                callcnt = --local->call_count;

                if (op_ret == -1) {
                        gf_log (this->name, GF_LOG_DEBUG, "%s returned %s",
                                prev->this->name, strerror (op_errno));
                        local->op_errno = op_errno;
                        if (op_errno != ENOENT) {
                                local->failed = 1;
                                local->op_ret = op_ret;
                        }
                }
        }
        UNLOCK (&frame->lock);

        if (callcnt == 1) {
                if (local->failed) {
                        op_errno = local->op_errno;
                        goto out;
                }
                STACK_WIND(frame, stripe_first_unlink_cbk, FIRST_CHILD (this),
                           FIRST_CHILD (this)->fops->unlink, &local->loc,
                           local->xflag, local->xdata);
        }
        return 0;
out:
        STRIPE_STACK_UNWIND (unlink, frame, -1, op_errno, NULL, NULL, NULL);

        return 0;
}
