mdc_getxattr (call_frame_t *frame, xlator_t *this, loc_t *loc, const char *key,
              dict_t *xdata)
{
        int           ret;
        mdc_local_t  *local = NULL;
	dict_t       *xattr = NULL;

        local = mdc_local_get (frame);
        if (!local)
                goto uncached;

        loc_copy (&local->loc, loc);

	if (!is_mdc_key_satisfied (key))
		goto uncached;

	ret = mdc_inode_xatt_get (this, loc->inode, &xattr);
	if (ret != 0)
		goto uncached;

	if (!dict_get (xattr, (char *)key))
		goto uncached;

        MDC_STACK_UNWIND (getxattr, frame, 0, 0, xattr, xdata);

        return 0;

uncached:
        STACK_WIND (frame, mdc_getxattr_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->getxattr,
                    loc, key, xdata);
        return 0;
}
