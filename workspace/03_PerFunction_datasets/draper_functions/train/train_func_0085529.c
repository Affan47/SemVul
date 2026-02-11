trace_readv_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                 int32_t op_ret, int32_t op_errno, struct iovec *vector,
                 int32_t count, struct iatt *buf, struct iobref *iobref,
                 dict_t *xdata)
{
        char          statstr[4096] = {0, };
        trace_conf_t  *conf         = NULL;

        conf = this->private;

        if (!conf->log_file && !conf->log_history)
		goto out;
        if (trace_fop_names[GF_FOP_READ].enabled) {
                char  string[4096] = {0,};
                if (op_ret >= 0) {
                        trace_stat_to_str (buf, statstr);
                        snprintf (string, sizeof (string),
                                  "%"PRId64": gfid=%s op_ret=%d buf=%s",
                                  frame->root->unique,
                                  uuid_utoa (frame->local), op_ret,
                                  statstr);
                } else {
                        snprintf (string, sizeof (string),
                                  "%"PRId64": gfid=%s op_ret=%d, "
                                  "op_errno=%d)",
                                  frame->root->unique,
                                  uuid_utoa (frame->local), op_ret,
                                  op_errno);
                }
                LOG_ELEMENT (conf, string);
        }
out:
        TRACE_STACK_UNWIND (readv, frame, op_ret, op_errno, vector, count,
                            buf, iobref, xdata);
        return 0;
}
