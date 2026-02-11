posix_acl_rmdir (call_frame_t *frame, xlator_t *this, loc_t *loc, int flags)
{
        if (!sticky_permits (frame, loc->parent, loc->inode))
                goto red;

        if (acl_permits (frame, loc->parent, POSIX_ACL_WRITE|POSIX_ACL_EXECUTE))
                goto green;
        else
                goto red;
green:
        STACK_WIND (frame, posix_acl_rmdir_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->rmdir,
                    loc, flags);
        return 0;
red:
        STACK_UNWIND_STRICT (rmdir, frame, -1, EACCES, NULL, NULL);
        return 0;
}
