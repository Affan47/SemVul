bus_summary(char *busname)
{
    discover_bus_t bus;
    discover_bus_map_t *busmap;
    discover_error_t *status;
    discover_device_t *devices;
    int i;


    status = discover_error_new();
    if (busname) {
        bus = discover_conf_name_to_bus(busname, status);
        check_status(status);
        devices = discover_get_devices(bus, status);
        check_status(status);

        print_device_list(devices);
    } else {
        busmap = discover_conf_get_full_bus_map(status);
        check_status(status);
        for (i = 0; busmap[i].name; i++) {
            if (busmap[i].scan_default) {
                devices = discover_get_devices(i, status);
                check_status(status);

                print_device_list(devices);

                memdebug_free(busmap[i]);
            }
        }
    }
    discover_error_free(status);
}
