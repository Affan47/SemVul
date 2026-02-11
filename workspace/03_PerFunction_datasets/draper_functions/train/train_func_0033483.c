kmc_list_devices(int action)
{
    int i;
    int serrno;

    for (i = 0; i < sizeof(devices) / sizeof(char *); i++) {
        dev_fd = open(devices[i], O_RDWR);
        serrno = errno;
        if ( dev_fd == -1 ) {
            if (  ! strcmp(sys_errlist[serrno],"Permission denied") ) {
                fprintf( stderr, "%s: Permission denied\n",devices[i]);
                }
            continue;
            }
        get_device_info();

	if (action == 0) printf("%s\n",devices[i]);
	if ( (action == 1) && is_a_kmc() ) printf("%s\n",devices[i]);
	if (action == 2) printf("%s \t%.8s \t%.16s\n",devices[i],vendor, product);
        close(dev_fd);
    }
    return 0;
}
