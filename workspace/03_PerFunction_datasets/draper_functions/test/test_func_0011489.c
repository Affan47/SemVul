nfs_fop_lk_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                int32_t op_ret, int32_t op_errno, struct gf_flock *flock,
                dict_t *xdata)
{
        struct nfs_fop_local    *nfl = NULL;
        fop_lk_cbk_t         progcbk = NULL;

        nfl_to_prog_data (nfl, progcbk, frame);

        if (!op_ret)
                fd_lk_insert_and_merge (nfl->fd, nfl->cmd, &nfl->flock);

        fd_unref (nfl->fd);

        if (progcbk)
                progcbk (frame, cookie, this, op_ret, op_errno, flock, xdata);

        nfs_stack_destroy (nfl, frame);
        return 0;
}
