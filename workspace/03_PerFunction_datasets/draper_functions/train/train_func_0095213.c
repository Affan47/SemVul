hiface_pcm_init_urb(struct pcm_urb *urb,
			       struct hiface_chip *chip,
			       unsigned int ep,
			       void (*handler)(struct urb *))
{
	urb->chip = chip;
	usb_init_urb(&urb->instance);

	urb->buffer = kzalloc(PCM_PACKET_SIZE, GFP_KERNEL);
	if (!urb->buffer)
		return -ENOMEM;

	usb_fill_bulk_urb(&urb->instance, chip->dev,
			  usb_sndbulkpipe(chip->dev, ep), (void *)urb->buffer,
			  PCM_PACKET_SIZE, handler, urb);
	init_usb_anchor(&urb->submitted);

	return 0;
}
