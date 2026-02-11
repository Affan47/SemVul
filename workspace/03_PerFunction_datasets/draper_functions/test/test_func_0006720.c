brcmf_usb_detach(struct brcmf_usbdev_info *devinfo)
{
	brcmf_dbg(USB, "Enter, devinfo %p\n", devinfo);


	brcmf_usb_free_q(&devinfo->rx_freeq, false);
	brcmf_usb_free_q(&devinfo->tx_freeq, false);

	usb_free_urb(devinfo->ctl_urb);
	usb_free_urb(devinfo->bulk_urb);

	kfree(devinfo->tx_reqs);
	kfree(devinfo->rx_reqs);
}
