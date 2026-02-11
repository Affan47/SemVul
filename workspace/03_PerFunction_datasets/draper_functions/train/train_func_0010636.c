rtl8187_disconnect(struct usb_interface *intf)
{
	struct ieee80211_hw *dev = usb_get_intfdata(intf);
	struct rtl8187_priv *priv;

	if (!dev)
		return;

#ifdef CONFIG_RTL8187_LEDS
	rtl8187_leds_exit(dev);
#endif
	rtl8187_rfkill_exit(dev);
	ieee80211_unregister_hw(dev);

	priv = dev->priv;
	usb_reset_device(priv->udev);
	usb_put_dev(interface_to_usbdev(intf));
	kfree(priv->io_dmabuf);
	ieee80211_free_hw(dev);
}
