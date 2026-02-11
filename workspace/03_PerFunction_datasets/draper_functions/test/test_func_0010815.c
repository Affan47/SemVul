posix_acl_readdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int op_ret, int op_errno, gf_dirent_t *entries,
                       dict_t *xdata)
{
        if (op_ret != 0)
                goto unwind;
unwind:
        STACK_UNWIND_STRICT (readdir, frame, op_ret, op_errno, entries, xdata);
        return 0;
}
