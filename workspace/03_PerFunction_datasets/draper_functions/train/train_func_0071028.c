ttusb_dec_alloc_iso_urbs(struct ttusb_dec *dec)
{
	int i;

	dprintk("%s\n", __func__);

	dec->iso_buffer = pci_zalloc_consistent(NULL,
						ISO_FRAME_SIZE * (FRAMES_PER_ISO_BUF * ISO_BUF_COUNT),
						&dec->iso_dma_handle);

	if (!dec->iso_buffer) {
		dprintk("%s: pci_alloc_consistent - not enough memory\n",
			__func__);
		return -ENOMEM;
	}

	for (i = 0; i < ISO_BUF_COUNT; i++) {
		struct urb *urb;

		if (!(urb = usb_alloc_urb(FRAMES_PER_ISO_BUF, GFP_ATOMIC))) {
			ttusb_dec_free_iso_urbs(dec);
			return -ENOMEM;
		}

		dec->iso_urb[i] = urb;
	}

	ttusb_dec_setup_urbs(dec);

	return 0;
}
