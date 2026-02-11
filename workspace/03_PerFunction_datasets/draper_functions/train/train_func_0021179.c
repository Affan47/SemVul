line6_create_audio_out_urbs(struct snd_line6_pcm *line6pcm)
{
	struct usb_line6 *line6 = line6pcm->line6;
	int i;


	for (i = 0; i < LINE6_ISO_BUFFERS; ++i) {
		struct urb *urb;


		urb = line6pcm->out.urbs[i] =
		    usb_alloc_urb(LINE6_ISO_PACKETS, GFP_KERNEL);

		if (urb == NULL)
			return -ENOMEM;

		urb->dev = line6->usbdev;
		urb->pipe =
		    usb_sndisocpipe(line6->usbdev,
				    line6->properties->ep_audio_w &
				    USB_ENDPOINT_NUMBER_MASK);
		urb->transfer_flags = URB_ISO_ASAP;
		urb->start_frame = -1;
		urb->number_of_packets = LINE6_ISO_PACKETS;
		urb->interval = LINE6_ISO_INTERVAL;
		urb->error_count = 0;
		urb->complete = audio_out_callback;
	}

	return 0;
}
