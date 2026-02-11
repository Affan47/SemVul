mdc_fstat (call_frame_t *frame, xlator_t *this, fd_t *fd, dict_t *xdata)
{
        int           ret;
        struct iatt   stbuf;
        mdc_local_t  *local = NULL;

        local = mdc_local_get (frame);
        if (!local)
                goto uncached;

        local->fd = fd_ref (fd);

        ret = mdc_inode_iatt_get (this, fd->inode, &stbuf);
        if (ret != 0)
                goto uncached;

        MDC_STACK_UNWIND (fstat, frame, 0, 0, &stbuf, xdata);

        return 0;

uncached:
        STACK_WIND (frame, mdc_fstat_cbk,
                    FIRST_CHILD(this), FIRST_CHILD(this)->fops->fstat,
                    fd, xdata);
        return 0;
}
