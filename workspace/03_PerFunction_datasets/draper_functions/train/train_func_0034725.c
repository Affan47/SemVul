get_strings()
{

    char vendor[512], desc[512], serial[512];

    int ret = ftdi_usb_get_strings(d->ftdi, d->dev, vendor, 512, desc, 512, serial, 512);

    if (ret < 0)
        return -1;

    d->vendor = vendor;
    d->description = desc;
    d->serial = serial;

    return 1;
}
