__is_dentry_cyclic (dentry_t *dentry)
{
        int       ret = 0;
        inode_t  *inode = NULL;
        char     *name = "<nul>";

        ret = __foreach_ancestor_dentry (dentry, __check_cycle,
                                         dentry->inode);
        if (ret) {
                inode = dentry->inode;

                if (dentry->name)
                        name = dentry->name;

                gf_log (dentry->inode->table->name, GF_LOG_CRITICAL,
                        "detected cyclic loop formation during inode linkage."
                        " inode (%s) linking under itself as %s",
                        uuid_utoa (inode->gfid), name);
        }

        return ret;
}
