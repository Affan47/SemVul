apm_exists(void)
{
    int fd;
    apm_info i;


    fd = open(APM_DEVICE, O_WRONLY);
    if (fd >= 0)
	close(fd);

    if (access(APM_PROC, R_OK))
	return 1;
    return apm_read(&i);
}
