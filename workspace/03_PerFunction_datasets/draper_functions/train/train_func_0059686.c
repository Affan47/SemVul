__inode_retire (inode_t *inode)
{
        dentry_t      *dentry = NULL;
        dentry_t      *t = NULL;

        if (!inode) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "inode not found");
                return;
        }

        list_move_tail (&inode->list, &inode->table->purge);
        inode->table->purge_size++;

        __inode_unhash (inode);

        list_for_each_entry_safe (dentry, t, &inode->dentry_list, inode_list) {
                __dentry_unset (dentry);
        }
}
