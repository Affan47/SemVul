nfs_fop_stat_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                  int32_t op_ret, int32_t op_errno, struct iatt *buf,
                  dict_t *xdata)
{
        struct nfs_fop_local    *nfl = NULL;
        fop_stat_cbk_t          progcbk = NULL;

        nfl_to_prog_data (nfl, progcbk, frame);
        nfs_fop_restore_root_ino (nfl, op_ret, buf, NULL, NULL, NULL);
        if (progcbk)
                progcbk (frame, cookie, this, op_ret, op_errno, buf, xdata);

        nfs_stack_destroy (nfl, frame);
        return 0;
}
