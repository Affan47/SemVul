nfs_fop_fstat (xlator_t *nfsx, xlator_t *xl, nfs_user_t *nfu, fd_t *fd,
               fop_fstat_cbk_t cbk, void *local)
{
        call_frame_t            *frame = NULL;
        int                     ret = -EFAULT;
        struct nfs_fop_local    *nfl = NULL;

        if ((!nfsx) || (!xl) || (!fd) || (!nfu))
                return ret;

        gf_log (GF_NFS, GF_LOG_TRACE, "FStat");
        nfs_fop_handle_frame_create (frame, nfsx, nfu, ret, err);
        nfs_fop_handle_local_init (frame, nfsx, nfl, cbk, local, ret, err);
        nfs_fop_save_root_fd_ino (nfl, fd);

        STACK_WIND_COOKIE (frame, nfs_fop_fstat_cbk, xl, xl, xl->fops->fstat,
                           fd, NULL);

        ret = 0;
err:
        if (ret < 0) {
                if (frame)
                        nfs_stack_destroy (nfl, frame);
        }

        return ret;
}
