write(char *buf, int bytes)
{


    if (!device) return -1;

    int rc;
    if (OperatingSystem == WINDOWS) {
        rc = usb_interrupt_write(device, writeEndpoint, buf, bytes, 1000);
    } else {


        rc = usb_bulk_write(device, writeEndpoint, buf, bytes, 125);
    }

    if (rc < 0)
    {


        qDebug()<<"usb_interrupt_write Error writing ["<<rc<<"]: "<< usb_strerror();
    }

    return rc;
}
