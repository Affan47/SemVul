efreet_setowner(const char *path)
{
    EINA_SAFETY_ON_NULL_RETURN(path);

    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0) return;
    efreet_fsetowner(fd);
    close(fd);
}
