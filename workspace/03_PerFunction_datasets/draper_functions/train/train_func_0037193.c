get_device(char fs_name)
{
    int i;

    if (fs_name < 'A' || fs_name > 'Z') {
        return ERROR_BAD_FS_NAME;
    }

    for (i = 0; i < MAX_DEVICE; i++) {
        if (device_array[i].fs_name == fs_name) {
            return i;
        }
    }

    return ERROR_FS_NAME_NOT_EXISTS;
}
