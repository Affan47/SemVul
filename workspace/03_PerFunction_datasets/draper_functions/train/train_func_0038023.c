posix_acl_setattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                       int op_ret, int op_errno,
                       struct iatt *prebuf, struct iatt *postbuf)
{
        inode_t   *inode = NULL;

        inode = frame->local;
        frame->local = NULL;

        if (op_ret != 0)
                goto unwind;

        posix_acl_ctx_update (inode, this, postbuf);

unwind:
        STACK_UNWIND_STRICT (setattr, frame, op_ret, op_errno, prebuf, postbuf);
        return 0;
}
