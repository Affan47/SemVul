posix_acl_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int op_ret, int op_errno, fd_t *fd, inode_t *inode,
                      struct iatt *buf, struct iatt *preparent,
                      struct iatt *postparent, dict_t *xdata)
{
        if (op_ret != 0)
                goto unwind;

        posix_acl_ctx_update (inode, this, buf);

unwind:
        STACK_UNWIND_STRICT (create, frame, op_ret, op_errno, fd, inode, buf,
                             preparent, postparent, xdata);
        return 0;
}
