inode_ctx_set2 (inode_t *inode, xlator_t *xlator, uint64_t *value1_p,
                uint64_t *value2_p)
{
        int ret = 0;

        if (!inode || !xlator)
                return -1;

        LOCK (&inode->lock);
        {
                ret = __inode_ctx_set2 (inode, xlator, value1_p, value2_p);
        }
        UNLOCK (&inode->lock);

        return ret;
}
