fop_stat_cbk_stub (call_frame_t *frame, fop_stat_cbk_t fn,
                   int32_t op_ret, int32_t op_errno,
                   struct iatt *buf, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);

        stub = stub_new (frame, 0, GF_FOP_STAT);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->fn_cbk.stat = fn;
        stub->args_cbk.op_ret = op_ret;
        stub->args_cbk.op_errno = op_errno;
        if (op_ret == 0)
                stub->args_cbk.stat = *buf;
        if (xdata)
                stub->args_cbk.xdata = dict_ref (xdata);
out:
        return stub;
}
