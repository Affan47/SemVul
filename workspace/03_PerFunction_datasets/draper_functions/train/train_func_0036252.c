msi2500_disconnect(struct usb_interface *intf)
{
	struct v4l2_device *v = usb_get_intfdata(intf);
	struct msi2500_dev *dev =
			container_of(v, struct msi2500_dev, v4l2_dev);

	dev_dbg(dev->dev, "\n");

	mutex_lock(&dev->vb_queue_lock);
	mutex_lock(&dev->v4l2_lock);

	dev->udev = NULL;
	v4l2_device_disconnect(&dev->v4l2_dev);
	video_unregister_device(&dev->vdev);
	spi_unregister_master(dev->master);
	mutex_unlock(&dev->v4l2_lock);
	mutex_unlock(&dev->vb_queue_lock);

	v4l2_device_put(&dev->v4l2_dev);
}
