msi2500_isoc_init(struct msi2500_dev *dev)
{
	struct urb *urb;
	int i, j, ret;

	dev_dbg(dev->dev, "\n");

	dev->isoc_errors = 0;

	ret = usb_set_interface(dev->udev, 0, 1);
	if (ret)
		return ret;


	for (i = 0; i < MAX_ISO_BUFS; i++) {
		urb = usb_alloc_urb(ISO_FRAMES_PER_DESC, GFP_KERNEL);
		if (urb == NULL) {
			dev_err(dev->dev, "Failed to allocate urb %d\n", i);
			msi2500_isoc_cleanup(dev);
			return -ENOMEM;
		}
		dev->urbs[i] = urb;
		dev_dbg(dev->dev, "Allocated URB at 0x%p\n", urb);

		urb->interval = 1;
		urb->dev = dev->udev;
		urb->pipe = usb_rcvisocpipe(dev->udev, 0x81);
		urb->transfer_flags = URB_ISO_ASAP | URB_NO_TRANSFER_DMA_MAP;
		urb->transfer_buffer = usb_alloc_coherent(dev->udev,
				ISO_BUFFER_SIZE,
				GFP_KERNEL, &urb->transfer_dma);
		if (urb->transfer_buffer == NULL) {
			dev_err(dev->dev,
				"Failed to allocate urb buffer %d\n", i);
			msi2500_isoc_cleanup(dev);
			return -ENOMEM;
		}
		urb->transfer_buffer_length = ISO_BUFFER_SIZE;
		urb->complete = msi2500_isoc_handler;
		urb->context = dev;
		urb->start_frame = 0;
		urb->number_of_packets = ISO_FRAMES_PER_DESC;
		for (j = 0; j < ISO_FRAMES_PER_DESC; j++) {
			urb->iso_frame_desc[j].offset = j * ISO_MAX_FRAME_SIZE;
			urb->iso_frame_desc[j].length = ISO_MAX_FRAME_SIZE;
		}
	}


	for (i = 0; i < MAX_ISO_BUFS; i++) {
		ret = usb_submit_urb(dev->urbs[i], GFP_KERNEL);
		if (ret) {
			dev_err(dev->dev,
				"usb_submit_urb %d failed with error %d\n",
				i, ret);
			msi2500_isoc_cleanup(dev);
			return ret;
		}
		dev_dbg(dev->dev, "URB 0x%p submitted.\n", dev->urbs[i]);
	}


	return 0;
}
