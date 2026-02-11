alloc_stream_urbs(struct ua101 *ua, struct ua101_stream *stream,
			     void (*urb_complete)(struct urb *))
{
	unsigned max_packet_size = stream->max_packet_bytes;
	struct ua101_urb *urb;
	unsigned int b, u = 0;

	for (b = 0; b < ARRAY_SIZE(stream->buffers); ++b) {
		unsigned int size = stream->buffers[b].size;
		u8 *addr = stream->buffers[b].addr;
		dma_addr_t dma = stream->buffers[b].dma;

		while (size >= max_packet_size) {
			if (u >= stream->queue_length)
				goto bufsize_error;
			urb = kmalloc(sizeof(*urb), GFP_KERNEL);
			if (!urb)
				return -ENOMEM;
			usb_init_urb(&urb->urb);
			urb->urb.dev = ua->dev;
			urb->urb.pipe = stream->usb_pipe;
			urb->urb.transfer_flags = URB_NO_TRANSFER_DMA_MAP;
			urb->urb.transfer_buffer = addr;
			urb->urb.transfer_dma = dma;
			urb->urb.transfer_buffer_length = max_packet_size;
			urb->urb.number_of_packets = 1;
			urb->urb.interval = 1;
			urb->urb.context = ua;
			urb->urb.complete = urb_complete;
			urb->urb.iso_frame_desc[0].offset = 0;
			urb->urb.iso_frame_desc[0].length = max_packet_size;
			stream->urbs[u++] = urb;
			size -= max_packet_size;
			addr += max_packet_size;
			dma += max_packet_size;
		}
	}
	if (u == stream->queue_length)
		return 0;
bufsize_error:
	dev_err(&ua->dev->dev, "internal buffer size error\n");
	return -ENXIO;
}
