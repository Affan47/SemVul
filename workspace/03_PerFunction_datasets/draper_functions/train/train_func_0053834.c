fop_readdirp_cbk_stub (call_frame_t *frame,
                       fop_readdirp_cbk_t fn,
                       int32_t op_ret,
                       int32_t op_errno,
                       gf_dirent_t *entries)
{
        call_stub_t *stub = NULL;
        gf_dirent_t *stub_entry = NULL, *entry = NULL;

        GF_VALIDATE_OR_GOTO ("call-stub", frame, out);

        stub = stub_new (frame, 0, GF_FOP_READDIRP);
        GF_VALIDATE_OR_GOTO ("call-stub", stub, out);

        stub->args.readdirp_cbk.fn = fn;
        stub->args.readdirp_cbk.op_ret = op_ret;
        stub->args.readdirp_cbk.op_errno = op_errno;
        INIT_LIST_HEAD (&stub->args.readdirp_cbk.entries.list);


        GF_VALIDATE_OR_GOTO ("call-stub", entries, out);

        if (op_ret > 0) {
                list_for_each_entry (entry, &entries->list, list) {
                        stub_entry = gf_dirent_for_name (entry->d_name);
                        if (!stub_entry)
                                goto out;
                        stub_entry->d_off = entry->d_off;
                        stub_entry->d_ino = entry->d_ino;
                        stub_entry->d_stat = entry->d_stat;
                        list_add_tail (&stub_entry->list,
                                       &stub->args.readdirp_cbk.entries.list);
                }
        }
out:
        return stub;
}
