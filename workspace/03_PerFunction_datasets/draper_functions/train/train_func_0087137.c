fop_fgetxattr_stub (call_frame_t *frame,
                    fop_fgetxattr_t fn,
                    fd_t *fd,
                    const char *name)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", fd, out);

        stub = stub_new (frame, 1, GF_FOP_FGETXATTR);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.fgetxattr.fn = fn;
        stub->args.fgetxattr.fd = fd_ref (fd);

        if (name)
                stub->args.fgetxattr.name = gf_strdup (name);
out:
        return stub;
}
