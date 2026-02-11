reinit_device(struct cgpu_info *cgpu)
{
	if (cgpu->deven == DEV_DISABLED)
		return;

#ifdef USE_USBUTILS

	if (cgpu->usbdev && cgpu->usbdev->handle)
		libusb_reset_device(cgpu->usbdev->handle);
#endif
	cgpu->drv->reinit_device(cgpu);
}
