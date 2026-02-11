usbOpenDevice(union filedescriptor *fdp, int vendor, char *vendorName,
			 int product, char *productName, int doReportIDs)
{
    struct usb_bus      *bus;
    struct usb_device   *dev;
    usb_dev_handle      *handle = NULL;
    int                 errorCode = USB_ERROR_NOTFOUND;
    static int          didUsbInit = 0;

    if(!didUsbInit){
        usb_init();
        didUsbInit = 1;
    }
    usb_find_busses();
    usb_find_devices();
    for(bus=usb_get_busses(); bus; bus=bus->next){
        for(dev=bus->devices; dev; dev=dev->next){
            if(dev->descriptor.idVendor == vendor && dev->descriptor.idProduct == product){
                char    string[256];
                int     len;
                handle = usb_open(dev);
                if(!handle){
                    errorCode = USB_ERROR_ACCESS;
                    fprintf(stderr, "Warning: cannot open USB device: %s\n",
			    usb_strerror());
                    continue;
                }
                if(vendorName == NULL && productName == NULL){
                    break;
                }

                len = usbGetStringAscii(handle, dev->descriptor.iManufacturer,
					0x0409, string, sizeof(string));
                if(len < 0){
                    errorCode = USB_ERROR_IO;
                    fprintf(stderr,
			    "Warning: cannot query manufacturer for device: %s\n",
			    usb_strerror());
                }else{
                    errorCode = USB_ERROR_NOTFOUND;

                    if(strcmp(string, vendorName) == 0){
                        len = usbGetStringAscii(handle, dev->descriptor.iProduct,
						0x0409, string, sizeof(string));
                        if(len < 0){
                            errorCode = USB_ERROR_IO;
                            fprintf(stderr,
				    "Warning: cannot query product for device: %s\n",
				    usb_strerror());
                        }else{
                            errorCode = USB_ERROR_NOTFOUND;

                            if(strcmp(string, productName) == 0)
                                break;
                        }
                    }
                }
                usb_close(handle);
                handle = NULL;
            }
        }
        if(handle)
            break;
    }
    if(handle != NULL){
        int rval, retries = 3;
        if(usb_set_configuration(handle, 1)){
            fprintf(stderr, "Warning: could not set configuration: %s\n",
		    usb_strerror());
        }


        while((rval = usb_claim_interface(handle, 0)) != 0 && retries-- > 0){
#ifdef LIBUSB_HAS_DETACH_KERNEL_DRIVER_NP
            if(usb_detach_kernel_driver_np(handle, 0) < 0){
                fprintf(stderr, "Warning: could not detach kernel HID driver: %s\n",
			usb_strerror());
            }
#endif
        }
        if(rval != 0)
            fprintf(stderr, "Warning: could not claim interface\n");


        errorCode = 0;
        fdp->pfd = (void *)handle;
        usesReportIDs = doReportIDs;
    }
    return errorCode;
}
