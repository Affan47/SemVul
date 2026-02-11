fop_fremovexattr_stub (call_frame_t *frame, fop_fremovexattr_t fn,
                       fd_t *fd, const char *name, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", fd, out);
        GF_VALIDATE_OR_GOTO ("call-stub", name, out);

        stub = stub_new (frame, 1, GF_FOP_FREMOVEXATTR);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->fn.fremovexattr = fn;
        stub->args.fd = fd_ref (fd);
        stub->args.name = gf_strdup (name);
        if (xdata)
                stub->args.xdata = dict_ref (xdata);
out:
        return stub;
}
