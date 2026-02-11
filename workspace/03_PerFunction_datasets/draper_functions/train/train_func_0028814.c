stripe_fgetxattr (call_frame_t *frame, xlator_t *this, fd_t *fd,
                  const char *name, dict_t *xdata)
{
        if (stripe_is_special_xattr (name)) {
                stripe_fgetxattr_from_everyone (frame, this, fd, name, xdata);
                goto out;
        }

        STACK_WIND (frame, stripe_internal_getxattr_cbk, FIRST_CHILD(this),
                    FIRST_CHILD(this)->fops->fgetxattr, fd, name, xdata);

out:
        return 0;
}
