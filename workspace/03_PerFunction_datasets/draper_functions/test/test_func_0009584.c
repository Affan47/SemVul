sd_stopN(struct gspca_dev *gspca_dev)
{
	struct usb_device *dev = gspca_dev->dev;

	usb_set_interface(dev, gspca_dev->iface, 0);

	stk1135_camera_disable(gspca_dev);

	PDEBUG(D_STREAM, "camera stopped");
}
