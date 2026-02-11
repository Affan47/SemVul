huawei_port_exists(const char *device)
{
    int ret;
    struct stat stat_ptr;


    ret = stat(device, &stat_ptr);
    if (ret < 0)
	return 0;


    return (S_ISCHR(stat_ptr.st_mode));
}
