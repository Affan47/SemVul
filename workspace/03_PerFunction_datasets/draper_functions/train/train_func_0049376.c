usbdev_drain(union filedescriptor *fd, int display)
{
  usb_dev_handle *udev = (usb_dev_handle *)fd->usb.handle;
  int rv;

  do {
    rv = usb_bulk_read(udev, fd->usb.rep, usbbuf, fd->usb.max_xfer, 100);
    if (rv > 0 && verbose >= 4)
      fprintf(stderr, "%s: usbdev_drain(): flushed %d characters\n",
	      progname, rv);
  } while (rv > 0);

  return 0;
}
