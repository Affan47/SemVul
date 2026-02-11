unlock(usb_dev_handle *udev)
{
    unsigned int command[5];
    unsigned int result[8];

    command[0] = ISP_UNLOCK;
    command[1] = UNLOCK_CODE;

    if (!USBReqISP(udev, command, result))
    {
        printf("unlock failed\n");
        return(0);
    }
    return(1);
}
