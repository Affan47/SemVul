find_all(int vendor, int product)
{
    struct ftdi_device_list* dlist = 0;
    struct ftdi_context ftdi;
    ftdi_init(&ftdi);
    ftdi_usb_find_all(&ftdi, &dlist, vendor, product);
    ftdi_deinit(&ftdi);
    return new List(dlist);
}

}
