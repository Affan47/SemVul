nfs_forget (xlator_t *this, inode_t *inode)
{
        int32_t                 ret = -1;
        uint64_t                ctx = 0;
        struct inode_op_queue  *inode_q = NULL;

        if (!inode || !this)
                return 0;
        ret = inode_ctx_del (inode, this, &ctx);
        if (!ret && ctx && !(IA_ISDIR (inode->ia_type))) {
                inode_q = (struct inode_op_queue *) (long) ctx;
                pthread_mutex_lock (&inode_q->qlock);
                {
                        nfs3_flush_inode_queue (inode_q, NULL, 0);
                }
                pthread_mutex_unlock (&inode_q->qlock);
        }

        return 0;
}
