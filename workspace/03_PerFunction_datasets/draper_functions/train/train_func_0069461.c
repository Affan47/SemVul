io_stats_forget (xlator_t *this, inode_t *inode)
{
        BUMP_FOP (FORGET);
        ios_stats_cleanup (this, inode);
        return 0;
}
