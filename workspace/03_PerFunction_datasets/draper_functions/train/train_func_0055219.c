nfs_inode_mkdir_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno, inode_t *inode,
                     struct iatt *buf, struct iatt *preparent,
                     struct iatt *postparent, dict_t *xdata)
{
        struct nfs_fop_local    *nfl = frame->local;
        fop_mkdir_cbk_t         progcbk = NULL;
        inode_t                 *linked_inode = NULL;

        if (op_ret == -1)
                goto do_not_link;

        linked_inode = inode_link (inode, nfl->parent, nfl->path, buf);

do_not_link:
        inodes_nfl_to_prog_data (nfl, progcbk, frame);
        if (progcbk)
                progcbk (frame, cookie, this, op_ret, op_errno, inode, buf,
                         preparent, postparent, xdata);

        if (linked_inode) {
                inode_lookup (linked_inode);
                inode_unref (linked_inode);
        }

        return 0;
}
