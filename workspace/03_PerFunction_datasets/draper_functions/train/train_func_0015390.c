netsnmp_large_fd_set_resize(netsnmp_large_fd_set * fdset, int setsize)
{
    int             fd_set_bytes;

    if (fdset->lfs_setsize == setsize)
        goto success;

    if (setsize > FD_SETSIZE) {
        fd_set_bytes = NETSNMP_FD_SET_BYTES(setsize);
        if (fdset->lfs_setsize > FD_SETSIZE) {
            fdset->lfs_setptr = realloc(fdset->lfs_setptr, fd_set_bytes);
            if (!fdset->lfs_setptr)
                goto out_of_mem;
        } else {
            fdset->lfs_setptr = malloc(fd_set_bytes);
            if (!fdset->lfs_setptr)
                goto out_of_mem;
            *fdset->lfs_setptr = fdset->lfs_set;
        }
    } else {
        if (fdset->lfs_setsize > FD_SETSIZE) {
            fdset->lfs_set = *fdset->lfs_setptr;
            free(fdset->lfs_setptr);
        }
        fdset->lfs_setptr = &fdset->lfs_set;
    }

#if defined(cygwin) || !defined(HAVE_WINSOCK_H)
    {
        int             i;


        for (i = fdset->lfs_setsize; i < setsize; i++)
            FD_CLR(i, fdset->lfs_setptr);
    }
#endif

    fdset->lfs_setsize = setsize;
#if !defined(cygwin) && defined(HAVE_WINSOCK_H)
    if (setsize < fdset->lfs_set.fd_count)
        fdset->lfs_set.fd_count = setsize;
#endif
success:
    return 1;

out_of_mem:
    fdset->lfs_setsize = 0;
#if !defined(cygwin) && defined(HAVE_WINSOCK_H)
    fdset->lfs_set.fd_count = 0;
#endif
    return 0;
}
