configure_ali1533_smc_ports_decoding(int vendor_id, int device_id, int cfgbase, int firbase, int sirbase, int print)
{
    struct pci_access *access;
    struct pci_dev *dev = NULL;
    struct pci_filter filter;
    int ports[2], port_previous_mode, i;


    int dummy;
    dummy = cfgbase;

    access = pci_alloc();
    if (access == NULL) {
        DEBUG("impossible to obtain PCI access");
        return 0;
    }
    DEBUG("initializing filter");
    pci_filter_init(access, &filter);
    filter.vendor = vendor_id;
    filter.device = device_id;

    pci_init(access);

    dev = find_pci_device(access, &filter);
    if (dev) {
        if (print) {
            print_ali1533_port_status(dev);
        } else {

            syslog(LOG_NOTICE,
                   "PCI device 0x%x:0x%x found at %02x:%02x:%02x. Configuring:",
                   vendor_id, device_id, dev->bus, dev->dev, dev->func);
            ports[0] = sirbase;
            ports[1] = firbase;
            for (i = 0; i < 2; i++) {
                port_previous_mode = set_ali1533_port(dev, ports[i], 1);
                if (port_previous_mode == 1) {
                    syslog(LOG_ERR,
                           "port 0x%x was already enabled", ports[i]
                        );
                } else {
                    syslog(LOG_NOTICE,
                           "enabled decoding of port 0x%x", ports[i]
                        );
                }
            }
        }
    }
    if (dev != NULL) {
        syslog(LOG_NOTICE,
               "PCI device 0x%x:0x%x. Configuration ended",
               vendor_id, device_id);

    } else {
        syslog(LOG_ERR, "PCI device 0x%x:0x%x not found", vendor_id,
               device_id);
    }
    pci_cleanup(access);
    return dev != NULL;
}
