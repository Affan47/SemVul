usb_alloc_urb(int iso_packets, gfp_t mem_flags)
{
	struct urb *urb;

	urb = kmalloc(sizeof(struct urb) +
		iso_packets * sizeof(struct usb_iso_packet_descriptor),
		mem_flags);
	if (!urb) {
		printk(KERN_ERR "alloc_urb: kmalloc failed\n");
		return NULL;
	}
	usb_init_urb(urb);
	return urb;
}
