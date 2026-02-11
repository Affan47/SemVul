alloc_urbs(struct snd_usb_caiaqdev *cdev, int dir, int *ret)
{
	int i, frame;
	struct urb **urbs;
	struct usb_device *usb_dev = cdev->chip.dev;
	struct device *dev = caiaqdev_to_dev(cdev);
	unsigned int pipe;

	pipe = (dir == SNDRV_PCM_STREAM_PLAYBACK) ?
		usb_sndisocpipe(usb_dev, ENDPOINT_PLAYBACK) :
		usb_rcvisocpipe(usb_dev, ENDPOINT_CAPTURE);

	urbs = kmalloc(N_URBS * sizeof(*urbs), GFP_KERNEL);
	if (!urbs) {
		dev_err(dev, "unable to kmalloc() urbs, OOM!?\n");
		*ret = -ENOMEM;
		return NULL;
	}

	for (i = 0; i < N_URBS; i++) {
		urbs[i] = usb_alloc_urb(FRAMES_PER_URB, GFP_KERNEL);
		if (!urbs[i]) {
			dev_err(dev, "unable to usb_alloc_urb(), OOM!?\n");
			*ret = -ENOMEM;
			return urbs;
		}

		urbs[i]->transfer_buffer =
			kmalloc(FRAMES_PER_URB * BYTES_PER_FRAME, GFP_KERNEL);
		if (!urbs[i]->transfer_buffer) {
			dev_err(dev, "unable to kmalloc() transfer buffer, OOM!?\n");
			*ret = -ENOMEM;
			return urbs;
		}

		for (frame = 0; frame < FRAMES_PER_URB; frame++) {
			struct usb_iso_packet_descriptor *iso =
				&urbs[i]->iso_frame_desc[frame];

			iso->offset = BYTES_PER_FRAME * frame;
			iso->length = BYTES_PER_FRAME;
		}

		urbs[i]->dev = usb_dev;
		urbs[i]->pipe = pipe;
		urbs[i]->transfer_buffer_length = FRAMES_PER_URB
						* BYTES_PER_FRAME;
		urbs[i]->context = &cdev->data_cb_info[i];
		urbs[i]->interval = 1;
		urbs[i]->number_of_packets = FRAMES_PER_URB;
		urbs[i]->complete = (dir == SNDRV_PCM_STREAM_CAPTURE) ?
					read_completed : write_completed;
	}

	*ret = 0;
	return urbs;
}
