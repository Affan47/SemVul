fop_truncate_stub (call_frame_t *frame, fop_truncate_t fn,
                   loc_t *loc, off_t off, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);
        GF_VALIDATE_OR_GOTO ("call-stub", loc, out);

        stub = stub_new (frame, 1, GF_FOP_TRUNCATE);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->fn.truncate = fn;
        loc_copy (&stub->args.loc, loc);
        stub->args.offset = off;
        if (xdata)
                stub->args.xdata = dict_ref (xdata);
out:
        return stub;
}
