get_device_by_name(char *dname)
{
    int i;

    i = 0;
    while (i < ndevices) {
        if (strncmp(device_table[i].name, dname, strlen(dname)) == 0) {
            break;
        } else {
            i++;
        }
    }
    if (i >= ndevices) {
        return -1;
    } else {
	return i;
    }
}
