fop_open_stub (call_frame_t *frame,
               fop_open_t fn,
               loc_t *loc,
               int32_t flags, fd_t *fd,
               dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", loc, out);

        stub = stub_new (frame, 1, GF_FOP_OPEN);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.open.fn = fn;
        loc_copy (&stub->args.open.loc, loc);
        stub->args.open.flags = flags;
        if (fd)
                stub->args.open.fd = fd_ref (fd);
        if (xdata)
                stub->xdata = dict_ref (xdata);

out:
        return stub;
}
