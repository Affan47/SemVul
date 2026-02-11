chaoskey_free(struct chaoskey *dev)
{
	usb_dbg(dev->interface, "free");
	kfree(dev->name);
	kfree(dev->buf);
	kfree(dev);
}
