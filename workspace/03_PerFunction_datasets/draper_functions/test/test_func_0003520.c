fop_fxattrop_stub (call_frame_t *frame, fop_fxattrop_t fn,
                   fd_t *fd, gf_xattrop_flags_t optype,
                   dict_t *xattr, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", xattr, out);

        stub = stub_new (frame, 1, GF_FOP_FXATTROP);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->fn.fxattrop = fn;

        stub->args.fd = fd_ref (fd);

        stub->args.optype = optype;
        stub->args.xattr = dict_ref (xattr);

        if (xdata)
                stub->args.xdata = dict_ref (xdata);
out:
        return stub;
}
