io_stats_create_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, fd_t *fd,
                     inode_t *inode, struct iatt *buf,
                     struct iatt *preparent, struct iatt *postparent)
{
        struct ios_fd *iosfd = NULL;
        char          *path = NULL;
        struct ios_stat *iosstat = NULL;
        struct ios_conf   *conf = NULL;

        conf = this->private;

        path = frame->local;
        frame->local = NULL;

        if (!path)
                goto unwind;

        if (op_ret < 0) {
                GF_FREE (path);
                goto unwind;
        }

        iosfd = GF_CALLOC (1, sizeof (*iosfd), gf_io_stats_mt_ios_fd);
        if (!iosfd) {
                GF_FREE (path);
                goto unwind;
        }

        iosfd->filename = path;
        gettimeofday (&iosfd->opened_at, NULL);

        ios_fd_ctx_set (fd, this, iosfd);
        LOCK (&conf->lock);
        {
                conf->cumulative.nr_opens++;
                if (conf->cumulative.nr_opens > conf->cumulative.max_nr_opens) {
                        conf->cumulative.max_nr_opens = conf->cumulative.nr_opens;
                        conf->cumulative.max_openfd_time = iosfd->opened_at;
                }
        }
        UNLOCK (&conf->lock);

        iosstat = GF_CALLOC (1, sizeof (*iosstat), gf_io_stats_mt_ios_stat);
        if (!iosstat) {
                GF_FREE (path);
                goto unwind;
        }
        iosstat->filename = gf_strdup (path);
        uuid_copy (iosstat->gfid, buf->ia_gfid);
        LOCK_INIT (&iosstat->lock);
        ios_inode_ctx_set (fd->inode, this, iosstat);

unwind:
        UPDATE_PROFILE_STATS (frame, CREATE);
        STACK_UNWIND_STRICT (create, frame, op_ret, op_errno, fd, inode, buf,
                             preparent, postparent);
        return 0;
}
