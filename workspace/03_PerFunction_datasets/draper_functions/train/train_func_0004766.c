make_ref_datafile(const char *path)
{
    int fd;
    long counter;
    long value = 0;

    fd = dc_creat(path, 0644);

    if( fd < 0 ) {
	dc_perror("dc_creat:");
        return 0;
    }

    dc_unsafeWrite(fd);
    dc_setBufferSize(fd, 1024*1024);

    for( counter = 0; counter < 100*1024*1024; counter++) {
	value = htonl(counter * sizeof(long));
	dc_write(fd, &value, sizeof(long));
    }

    dc_close(fd);
    return 1;
}
