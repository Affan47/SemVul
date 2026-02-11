fop_setxattr_stub (call_frame_t *frame,
                   fop_setxattr_t fn,
                   loc_t *loc,
                   dict_t *dict,
                   int32_t flags)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", loc, out);

        stub = stub_new (frame, 1, GF_FOP_SETXATTR);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.setxattr.fn = fn;
        loc_copy (&stub->args.setxattr.loc, loc);

        if (dict)
                stub->args.setxattr.dict = dict_ref (dict);
        stub->args.setxattr.flags = flags;
out:
        return stub;
}
