fop_getxattr_cbk_stub (call_frame_t *frame,
                       fop_getxattr_cbk_t fn,
                       int32_t op_ret,
                       int32_t op_errno,
                       dict_t *dict, dict_t *xdata)
{
        call_stub_t *stub = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);

        stub = stub_new (frame, 0, GF_FOP_GETXATTR);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.getxattr_cbk.fn = fn;
        stub->args.getxattr_cbk.op_ret = op_ret;
        stub->args.getxattr_cbk.op_errno = op_errno;

        if (dict)
                stub->args.getxattr_cbk.dict = dict_ref (dict);
        if (xdata)
                stub->xdata = dict_ref (xdata);

out:
        return stub;
}
