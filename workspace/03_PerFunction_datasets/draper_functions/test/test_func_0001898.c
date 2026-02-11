usbvision_set_audio(struct usb_usbvision *usbvision, int audio_channel)
{
	if (!usbvision->audio_mute) {
		if (usbvision_write_reg(usbvision, USBVISION_IOPIN_REG, audio_channel) < 0) {
			printk(KERN_ERR "usbvision_set_audio: can't write iopin register for audio switching\n");
			return -1;
		}
	}
	usbvision->audio_channel = audio_channel;
	return 0;
}
