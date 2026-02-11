read_device_sysfs(ompi_btl_usnic_module_t *module, const char *name)
{
    int ret, fd;
    char filename[OPAL_PATH_MAX], line[256];

    snprintf(filename, sizeof(filename), "/sys/class/infiniband/%s/%s",
             ibv_get_device_name(module->device), name);
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        return -1;
    }

    ret = read(fd, line, sizeof(line));
    close(fd);
    if (ret < 0) {
        return -1;
    }

    return atoi(line);
}
