is_last_instance(void)
{
    int fd;
    int proccount = 0;
    int br;

    fd = open(PROCCOUNTFILE, O_RDONLY);
    br = read(fd, &proccount, sizeof(int));
    close(fd);
    return ((proccount == 1) || (br < 0) || fd < 0);
}
