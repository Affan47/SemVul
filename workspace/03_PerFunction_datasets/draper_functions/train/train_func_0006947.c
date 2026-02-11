filter_dump(void)
{
    int     fd;
    char    path[_POSIX_PATH_MAX], tmppath[_POSIX_PATH_MAX];
    struct  stat sts;

    log_message_level(LOG_LEVEL_SERVER, "filter_dump: dumping filter database");
    snprintf(tmppath, sizeof(tmppath), "%s/filter.tmp", global.varDir);
    if((fd = open(tmppath, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR ))==-1)
    {
        logerr("filter_dump", tmppath);
        return -1;
    }
    hash_foreach(global.filterHash, (hash_callback_t) dump_filter, (void *) fd);
    if(fstat(fd,&sts)==-1)
	{
        log_message_level(LOG_LEVEL_SERVER,  "filter_dump: fstat failed!");
        return 0;
    }
    if(sts.st_size==0)
	{
        log_message_level(LOG_LEVEL_SERVER,  "filter_dump: fstat on filter.tmp returned 0 file size!");
        return 0;
    }
    if(close(fd))
    {
        logerr("filter_dump", "close");
        return -1;
    }
    snprintf(path, sizeof(path), "%s/filter", global.varDir);
    if(stat(path, &sts) == -1 && errno == ENOENT)
    {
        log_message_level(LOG_LEVEL_DEBUG, "%s file does not exist\n", path);
    }
    else
    {
        if(unlink(path))
            logerr("filter_dump", "unlink");
    }
    if(rename(tmppath, path))
    {
        logerr("filter_dump", "rename");
        return -1;
    }
    return 0;
}
