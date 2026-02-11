__fd_lookup_anonymous (inode_t *inode)
{
        fd_t *iter_fd = NULL;
        fd_t *fd = NULL;

        if (list_empty (&inode->fd_list))
                return NULL;

        list_for_each_entry (iter_fd, &inode->fd_list, inode_list) {
                if (iter_fd->anonymous) {
                        fd = __fd_ref (iter_fd);
                        break;
                }
        }

        return fd;
}
