register_usb_transport(usb_handle *usb, const char *serial, const char *devpath, unsigned writeable)
{
    atransport *t = calloc(1, sizeof(atransport));
    D("transport: %p init'ing for usb_handle %p (sn='%s')\n", t, usb,
      serial ? serial : "");
    init_usb_transport(t, usb, (writeable ? CS_OFFLINE : CS_NOPERM));
    if(serial) {
        t->serial = strdup(serial);
    }
    if(devpath) {
        t->devpath = strdup(devpath);
    }
    register_transport(t);
}
