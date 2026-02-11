posix_acl_rename_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int op_ret, int op_errno, struct iatt *buf,
                      struct iatt *preoldparent, struct iatt *postoldparent,
                      struct iatt *prenewparent, struct iatt *postnewparent)
{
        if (op_ret != 0)
                goto unwind;
unwind:
        STACK_UNWIND_STRICT (rename, frame, op_ret, op_errno, buf,
                             preoldparent, postoldparent,
                             prenewparent, postnewparent);
        return 0;
}
