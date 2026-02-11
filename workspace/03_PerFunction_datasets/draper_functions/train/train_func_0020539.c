fill_connect_data(char *buf, size_t bufsize)
{
#if ADB_HOST
    return snprintf(buf, bufsize, "host::") + 1;
#else
    static const char *cnxn_props[] = {
        "ro.product.name",
        "ro.product.model",
        "ro.product.device",
    };
    static const int num_cnxn_props = ARRAY_SIZE(cnxn_props);
    static const char *values[] = {
        "occam",
        "Nexus 4",
        "mako",
    };
    int i;
    size_t remaining = bufsize;
    size_t len;

    len = snprintf(buf, remaining, "%s::", adb_device_banner);
    remaining -= len;
    buf += len;
    for (i = 0; i < num_cnxn_props; i++) {
        char value[PROPERTY_VALUE_MAX];

        len = snprintf(buf, remaining, "%s=%s;", cnxn_props[i], values[i]);
        remaining -= len;
        buf += len;
    }

    return bufsize - remaining + 1;
#endif
}
