posix_acl_ftruncate (call_frame_t *frame, xlator_t *this, fd_t *fd,
                     off_t offset)
{
        if (__is_fuse_call (frame))
                goto green;

        if (acl_permits (frame, fd->inode, POSIX_ACL_WRITE))
                goto green;
        else
                goto red;

green:
        STACK_WIND (frame, posix_acl_ftruncate_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->ftruncate,
                    fd, offset);
        return 0;
red:
        STACK_UNWIND_STRICT (ftruncate, frame, -1, EACCES, NULL, NULL);
        return 0;
}
