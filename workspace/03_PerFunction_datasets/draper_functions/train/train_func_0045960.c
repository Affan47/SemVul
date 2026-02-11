do_send(int s, char *path, char *buffer)
{
    char *tmp;
    mode_t mode;
    int is_link, ret;

    tmp = strrchr(path,',');
    if(tmp) {
        *tmp = 0;
        errno = 0;
        mode = strtoul(tmp + 1, NULL, 0);
#ifndef HAVE_SYMLINKS
        is_link = 0;
#else
        is_link = S_ISLNK(mode);
#endif
        mode &= 0777;
    }
    if(!tmp || errno) {
        mode = 0644;
        is_link = 0;
    }

    adb_unlink(path);


#ifdef HAVE_SYMLINKS
    if(is_link)
        ret = handle_send_link(s, path, buffer);
    else {
#else
    {
#endif

        mode |= ((mode >> 3) & 0070);
        mode |= ((mode >> 3) & 0007);

        ret = handle_send_file(s, path, mode, buffer);
    }

    return ret;
}
