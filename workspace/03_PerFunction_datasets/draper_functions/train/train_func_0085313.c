setLCDContrast(unsigned int level)
{
    int retval = 0;
    unsigned char usb_data[] = { 2, 32, 129, 0 };

    if(shared_device>0)
        return G15_ERROR_UNSUPPORTED;

    switch(level)
    {
        case 1:
            usb_data[3] = 22;
            break;
        case 2:
            usb_data[3] = 26;
            break;
        default:
            usb_data[3] = 18;
    }
    pthread_mutex_lock(&libusb_mutex);
    retval = usb_control_msg(keyboard_device, USB_TYPE_CLASS + USB_RECIP_INTERFACE, 9, 0x302, 0, (char*)usb_data, 4, 10000);
    pthread_mutex_unlock(&libusb_mutex);
    return retval;
}
