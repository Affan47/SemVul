standard_magic(archive_file_ty *afp)
{
    int             nbytes;
    char            magic[SARMAG];

    nbytes = read(afp->fd, magic, sizeof(magic));
    if (nbytes < 0)
        return -1;
    if (nbytes != sizeof(magic) || memcmp(magic, ARMAG, sizeof(magic)))
    {
        errno = EINVAL;
        return -1;
    }
    afp->start = sizeof(magic);
    return 0;
}
