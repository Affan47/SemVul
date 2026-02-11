nfs_inode_open_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int32_t op_ret, int32_t op_errno, fd_t *fd)
{

        struct nfs_fop_local    *nfl = NULL;
        fop_open_cbk_t          progcbk = NULL;

        if ((op_ret == -1) && (fd))
                fd_unref (fd);


        inodes_nfl_to_prog_data (nfl, progcbk, frame);
        if (progcbk)
                progcbk (frame, cookie, this, op_ret, op_errno, fd);
        return 0;
}
