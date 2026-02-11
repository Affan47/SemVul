findAntStick()
{
    struct usb_bus* bus;
    struct usb_device* dev;
    bool found = false;
    for (bus = usb_get_busses(); bus; bus = bus->next) {

        for (dev = bus->devices; dev; dev = dev->next) {

            if (dev->descriptor.idVendor == GARMIN_USB2_VID &&
                (dev->descriptor.idProduct == GARMIN_USB2_PID || dev->descriptor.idProduct == GARMIN_OEM_PID)) {
                found = true;
            }
        }
    }
    return found;
}
