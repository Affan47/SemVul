get_vendor_keys(struct listnode *list)
{
    const char *adb_keys_path;
    char keys_path[MAX_PAYLOAD];
    char *path;
    char *save;
    struct stat buf;

    adb_keys_path = getenv("ADB_VENDOR_KEYS");
    if (!adb_keys_path)
        return;
    strncpy(keys_path, adb_keys_path, sizeof(keys_path));

    path = adb_strtok_r(keys_path, ENV_PATH_SEPARATOR_STR, &save);
    while (path) {
        D("Reading: '%s'\n", path);

        if (stat(path, &buf))
            D("Can't read '%s'\n", path);
        else if (!read_key(path, list))
            D("Failed to read '%s'\n", path);

        path = adb_strtok_r(NULL, ENV_PATH_SEPARATOR_STR, &save);
    }
}
