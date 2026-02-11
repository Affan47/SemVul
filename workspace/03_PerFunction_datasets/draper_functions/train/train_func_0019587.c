cook_device(char *dev)
{
    static char     cooked_dev[SNMP_MAXPATH+1];

    if (!strncmp(dev, RAW_DEVICE_PREFIX, strlen(RAW_DEVICE_PREFIX))) {
        strlcpy(cooked_dev, COOKED_DEVICE_PREFIX, sizeof(cooked_dev));
        strlcat(cooked_dev, dev + strlen(RAW_DEVICE_PREFIX),
                sizeof(cooked_dev));
    } else {
        strlcpy(cooked_dev, dev, sizeof(cooked_dev));
    }

    return cooked_dev;
}
