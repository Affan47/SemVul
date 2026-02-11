syncop_lk (xlator_t *subvol, fd_t *fd, int cmd, struct gf_flock *flock)
{
        struct syncargs args = {0, };

        SYNCOP (subvol, (&args), syncop_lk_cbk, subvol->fops->lk,
                fd, cmd, flock, NULL);

        errno = args.op_errno;
	*flock = args.flock;

        return args.op_ret;
}
