globus_l_gfs_getgrnam(
    const char *                        name)
{
    struct group *                      grent;
    struct group *                      grent_copy = NULL;

    globus_libc_lock();
    grent = getgrnam(name);
    if(grent != NULL)
    {
        grent_copy = globus_l_gfs_gr_copy(grent);
    }
    globus_libc_unlock();

    return grent_copy;
}
