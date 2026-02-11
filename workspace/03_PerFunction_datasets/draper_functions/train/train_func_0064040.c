sd_start(struct gspca_dev *gspca_dev)
{
	struct urb *urb;
	int i, n;


#if MAX_NURBS < 4
#error "Not enough URBs in the gspca table"
#endif
#define SD_PKT_SZ 64
#define SD_NPKT 32
	for (n = 0; n < 4; n++) {
		urb = usb_alloc_urb(SD_NPKT, GFP_KERNEL);
		if (!urb) {
			pr_err("usb_alloc_urb failed\n");
			return -ENOMEM;
		}
		gspca_dev->urb[n] = urb;
		urb->transfer_buffer = usb_alloc_coherent(gspca_dev->dev,
						SD_PKT_SZ * SD_NPKT,
						GFP_KERNEL,
						&urb->transfer_dma);

		if (urb->transfer_buffer == NULL) {
			pr_err("usb_alloc_coherent failed\n");
			return -ENOMEM;
		}
		urb->dev = gspca_dev->dev;
		urb->context = gspca_dev;
		urb->transfer_buffer_length = SD_PKT_SZ * SD_NPKT;
		urb->pipe = usb_rcvisocpipe(gspca_dev->dev,
					n & 1 ? 0x82 : 0x83);
		urb->transfer_flags = URB_ISO_ASAP
					| URB_NO_TRANSFER_DMA_MAP;
		urb->interval = 1;
		urb->complete = sd_isoc_irq;
		urb->number_of_packets = SD_NPKT;
		for (i = 0; i < SD_NPKT; i++) {
			urb->iso_frame_desc[i].length = SD_PKT_SZ;
			urb->iso_frame_desc[i].offset = SD_PKT_SZ * i;
		}
	}

	return gspca_dev->usb_err;
}
