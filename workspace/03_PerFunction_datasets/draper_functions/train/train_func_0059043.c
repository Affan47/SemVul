xhci_calculate_intel_u2_timeout(
		struct usb_device *udev,
		struct usb_endpoint_descriptor *desc)
{
	unsigned long long timeout_ns;
	unsigned long long u2_del_ns;

	timeout_ns = 10 * 1000 * 1000;

	if ((usb_endpoint_xfer_int(desc) || usb_endpoint_xfer_isoc(desc)) &&
			(xhci_service_interval_to_ns(desc) > timeout_ns))
		timeout_ns = xhci_service_interval_to_ns(desc);

	u2_del_ns = le16_to_cpu(udev->bos->ss_cap->bU2DevExitLat) * 1000ULL;
	if (u2_del_ns > timeout_ns)
		timeout_ns = u2_del_ns;

	return timeout_ns;
}
