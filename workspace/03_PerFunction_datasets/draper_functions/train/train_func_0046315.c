snd_usb_caiaq_midi_output_done(struct urb* urb)
{
	struct snd_usb_caiaqdev *cdev = urb->context;

	cdev->midi_out_active = 0;
	if (urb->status != 0)
		return;

	if (!cdev->midi_out_substream)
		return;

	snd_usb_caiaq_midi_send(cdev, cdev->midi_out_substream);
}
