syncop_writev (xlator_t *subvol, fd_t *fd, const struct iovec *vector,
               int32_t count, off_t offset, struct iobref *iobref,
               uint32_t flags)
{
        struct syncargs args = {0, };

        SYNCOP (subvol, (&args), syncop_writev_cbk, subvol->fops->writev,
                fd, (struct iovec *) vector, count, offset, flags, iobref,
		NULL);

        errno = args.op_errno;
        return args.op_ret;
}
