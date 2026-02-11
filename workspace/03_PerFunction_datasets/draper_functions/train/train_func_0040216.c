cx231xx_uninit_isoc(struct cx231xx *dev)
{
	struct cx231xx_dmaqueue *dma_q = &dev->video_mode.vidq;
	struct urb *urb;
	int i;

	cx231xx_isocdbg("cx231xx: called cx231xx_uninit_isoc\n");

	dev->video_mode.isoc_ctl.nfields = -1;
	for (i = 0; i < dev->video_mode.isoc_ctl.num_bufs; i++) {
		urb = dev->video_mode.isoc_ctl.urb[i];
		if (urb) {
			if (!irqs_disabled())
				usb_kill_urb(urb);
			else
				usb_unlink_urb(urb);

			if (dev->video_mode.isoc_ctl.transfer_buffer[i]) {
				usb_free_coherent(dev->udev,
						  urb->transfer_buffer_length,
						  dev->video_mode.isoc_ctl.
						  transfer_buffer[i],
						  urb->transfer_dma);
			}
			usb_free_urb(urb);
			dev->video_mode.isoc_ctl.urb[i] = NULL;
		}
		dev->video_mode.isoc_ctl.transfer_buffer[i] = NULL;
	}

	kfree(dev->video_mode.isoc_ctl.urb);
	kfree(dev->video_mode.isoc_ctl.transfer_buffer);
	kfree(dma_q->p_left_data);

	dev->video_mode.isoc_ctl.urb = NULL;
	dev->video_mode.isoc_ctl.transfer_buffer = NULL;
	dev->video_mode.isoc_ctl.num_bufs = 0;
	dma_q->p_left_data = NULL;

	if (dev->mode_tv == 0)
		cx231xx_capture_start(dev, 0, Raw_Video);
	else
		cx231xx_capture_start(dev, 0, TS1_serial_mode);


}
