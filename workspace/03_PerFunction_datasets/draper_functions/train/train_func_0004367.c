dump_pid(void)
{
    int     fd;
    char    path[_POSIX_PATH_MAX];
    char    outbuf[128];

    log_message_level(LOG_LEVEL_DEBUG, "dump_pid: pid is %d", getpid());
    snprintf(path, sizeof(path), "%s/opennap-ng.pid", global.varDir);
    if((fd = open(path, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR))==-1)
    {
        logerr("dump_pid", path);
        return;
    }
    snprintf(outbuf, sizeof(outbuf), "%d\n", (int) getpid());
    fake_fputs(outbuf,fd);
    close(fd);
}
