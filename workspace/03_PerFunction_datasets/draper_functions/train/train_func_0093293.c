exitLibG15()
{
    int retval = G15_NO_ERROR;
    if (keyboard_device){
#ifndef SUN_LIBUSB
        retval = usb_release_interface (keyboard_device, 0);
        usleep(50*1000);
#endif
#if 0
        retval = usb_reset(keyboard_device);
        usleep(50*1000);
#endif
        usb_close(keyboard_device);
        keyboard_device=0;
        pthread_mutex_destroy(&libusb_mutex);
        return retval;
    }
    return -1;
}
