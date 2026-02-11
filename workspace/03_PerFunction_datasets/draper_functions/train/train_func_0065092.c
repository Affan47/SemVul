find_device_by_id(char *id, discover_error_t *status)
{
    discover_bus_map_t *busmap;
    discover_device_t *devices, *device;
    discover_device_t *result;
    int i;


    busmap = discover_conf_get_full_bus_map(status);
    check_status(status);
    result = NULL;
    for (i = 0; busmap[i].name; i++) {
        if (busmap[i].scan_default) {
            devices = discover_get_devices(i, status);
            check_status(status);
            for (device = devices; device; device = discover_device_get_next(device)) {
                char buf[11];
                sprintf(buf, "0x%4.4s%4.4s",
                        discover_device_get_vendor_id(device),
                        discover_device_get_model_id(device));
                if (strcmp(buf, id) == 0) {
                    result = discover_device_new();
                    discover_device_copy(device, result);
                    result->next = NULL;
                    break;
                }
            }
            discover_device_free(devices, 0);
            memdebug_free(busmap[i]);
        }
    }

    return result;
}
