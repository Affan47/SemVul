posix_acl_mknod (call_frame_t *frame, xlator_t *this, loc_t *loc, mode_t mode,
                 dev_t rdev, dict_t *params)
{
        mode_t  newmode = 0;

        newmode = mode;
        if (acl_permits (frame, loc->parent, POSIX_ACL_WRITE|POSIX_ACL_EXECUTE))
                goto green;
        else
                goto red;
green:
        newmode = posix_acl_inherit_file (this, loc, params, mode);

        STACK_WIND (frame, posix_acl_mknod_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->mknod,
                    loc, newmode, rdev, params);
        return 0;
red:
        STACK_UNWIND_STRICT (mknod, frame, -1, EACCES, NULL, NULL, NULL, NULL);
        return 0;
}
