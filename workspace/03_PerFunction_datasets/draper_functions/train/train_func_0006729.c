nfs_fop_fsync_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                   int32_t op_ret, int32_t op_errno, struct iatt *prebuf,
                   struct iatt *postbuf, dict_t *xdata)
{
        struct nfs_fop_local    *nfl = NULL;
        fop_fsync_cbk_t         progcbk = NULL;

        nfl_to_prog_data (nfl, progcbk, frame);
        nfs_fop_restore_root_ino (nfl, op_ret, prebuf, postbuf, NULL, NULL);
        if (progcbk)
                progcbk (frame, cookie, this, op_ret, op_errno, prebuf,
                         postbuf, xdata);

        nfs_stack_destroy (nfl, frame);
        return 0;
}
