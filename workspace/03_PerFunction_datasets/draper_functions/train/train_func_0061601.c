mdc_create (call_frame_t *frame, xlator_t *this, loc_t *loc, int flags,
            mode_t mode, mode_t umask, fd_t *fd, dict_t *xdata)
{
        mdc_local_t  *local = NULL;

        local = mdc_local_get (frame);

        loc_copy (&local->loc, loc);
        local->xattr = dict_ref (xdata);

        STACK_WIND (frame, mdc_create_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->create,
                    loc, flags, mode, umask, fd, xdata);
        return 0;
}
