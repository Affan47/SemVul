init_output_log_file (output_plugin *log, const char *file, int flags)
{
    FILE *fp;
    const char *mode = MODE_READ;
    int retry = 0;

    if (!file)
        return -1;

    log->path = file;
    log->flags = flags;


reopen:
    if ((fp = fopen(log->path, mode)) == NULL) {
        int e = errno;
        switch(e) {
            case EISDIR:
            case EFAULT:
            case EACCES:

                if(retry){
                    if(flags & CONFIG_VERBOSE )
                       elog("%s denied opening asset log '%s'", strerror(e), log->path);
                    return e;
                }
                log->path = PRADS_ASSETLOG;
                retry++;
                goto reopen;
            case ENOENT:
                mode = MODE_WRITE;
                goto reopen;
            default:
                if(flags & CONFIG_VERBOSE)
                   elog("Cannot open file %s: %s!", log->path, strerror(errno));
                return e;
        }

    } else {
        log->data = (void *) fp;

        if (*mode == 'w'){

            fprintf(fp, "asset,vlan,port,proto,service,[service-info],distance,discovered\n");
        }

        fclose(fp);


        if ((log->data = (void *) fopen(log->path, "a")) == NULL) {
            int e = errno;
            printf("Cannot open log file %s for append!\n", log->path);
            return e;
        }
    }

    return 0;
}
