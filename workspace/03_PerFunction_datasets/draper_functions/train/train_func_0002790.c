mdc_mknod (call_frame_t *frame, xlator_t *this, loc_t *loc,
           mode_t mode, dev_t rdev, mode_t umask, dict_t *xdata)
{
        mdc_local_t  *local = NULL;

        local = mdc_local_get (frame);

        loc_copy (&local->loc, loc);
        local->xattr = dict_ref (xdata);

        STACK_WIND (frame, mdc_mknod_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->mknod,
                    loc, mode, rdev, umask, xdata);
        return 0;
}
