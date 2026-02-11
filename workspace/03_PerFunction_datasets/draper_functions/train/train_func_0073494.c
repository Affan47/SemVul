fop_readv_stub (call_frame_t *frame,
                fop_readv_t fn,
                fd_t *fd,
                size_t size,
                off_t off, uint32_t flags, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);

        stub = stub_new (frame, 1, GF_FOP_READ);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.readv.fn = fn;
        if (fd)
                stub->args.readv.fd = fd_ref (fd);
        stub->args.readv.size  = size;
        stub->args.readv.off   = off;
        stub->args.readv.flags = flags;

        if (xdata)
                stub->xdata = dict_ref (xdata);

out:
        return stub;
}
