lk_properties_save(void)
{
    int fd;
    uint32_t i,j;
    char * fname;
    char * buf;
    struct utimbuf time;

    if (properties_updated == 0)
        return 0;

    fname=lk_path_string("fileinfo");
    if(mk_path(fname) == -1){
        free(fname);
        return -1;
    }
    fd=open(fname,O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    if(fd==-1) {
        free(fname);
        lk_errors_set(E_OPEN);
        return -1;
    }

    for(i=0,j=16; i<props.count; j++) {
        if(props.fidTable[j]){
            buf=lk_properties_export(j*16);
            write(fd, buf, strlen(buf));
            free(buf);
            write(fd, "\n", 1);
            ++i;
        }
    }
    close(fd);

    time.actime=device_generation;
    time.modtime=time.actime;
    if(utime(fname, &time)==-1){
        free(fname);
        lk_errors_set(E_UTIME);
        return -1;
    }

    free(fname);

    if (fdb_updated != 0)
        return lk_fdb_save();

    return 0;
}
