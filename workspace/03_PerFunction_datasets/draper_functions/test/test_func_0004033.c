fop_readv_cbk_stub (call_frame_t *frame, fop_readv_cbk_t fn,
                    int32_t op_ret, int32_t op_errno, struct iovec *vector,
		    int32_t count, struct iatt *stbuf,
                    struct iobref *iobref, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);

        stub = stub_new (frame, 0, GF_FOP_READ);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->fn_cbk.readv = fn;
        stub->args_cbk.op_ret = op_ret;
        stub->args_cbk.op_errno = op_errno;
        if (op_ret >= 0) {
                stub->args_cbk.vector = iov_dup (vector, count);
                stub->args_cbk.count = count;
                stub->args_cbk.stat = *stbuf;
                stub->args_cbk.iobref = iobref_ref (iobref);
        }
        if (xdata)
                stub->args_cbk.xdata = dict_ref (xdata);
out:
        return stub;
}
