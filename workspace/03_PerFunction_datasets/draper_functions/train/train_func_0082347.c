__fd_has_locks (pl_inode_t *pl_inode, fd_t *fd)
{
        int           found = 0;
        posix_lock_t *l     = NULL;

        list_for_each_entry (l, &pl_inode->ext_list, list) {
                if ((l->fd_num == fd_to_fdnum(fd))) {
                        found = 1;
                        break;
                }
        }

        return found;
}
