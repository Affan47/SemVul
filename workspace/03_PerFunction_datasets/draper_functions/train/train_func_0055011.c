netsnmp_large_fd_setfd(int fd, netsnmp_large_fd_set * fdset)
{
    netsnmp_assert(fd >= 0);

    while (fd >= (int)fdset->lfs_setsize)
        netsnmp_large_fd_set_resize(fdset, 2 * (fdset->lfs_setsize + 1));

    FD_SET(fd, fdset->lfs_setptr);
}
