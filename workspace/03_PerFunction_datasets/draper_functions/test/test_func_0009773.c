fop_readv_cbk_stub (call_frame_t *frame,
                    fop_readv_cbk_t fn,
                    int32_t op_ret,
                    int32_t op_errno,
                    struct iovec *vector,
                    int32_t count,
                    struct iatt *stbuf,
                    struct iobref *iobref)

{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);

        stub = stub_new (frame, 0, GF_FOP_READ);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.readv_cbk.fn = fn;
        stub->args.readv_cbk.op_ret = op_ret;
        stub->args.readv_cbk.op_errno = op_errno;
        if (op_ret >= 0) {
                stub->args.readv_cbk.vector = iov_dup (vector, count);
                stub->args.readv_cbk.count = count;
                stub->args.readv_cbk.stbuf = *stbuf;
                stub->args.readv_cbk.iobref = iobref_ref (iobref);
        }
out:
        return stub;
}
