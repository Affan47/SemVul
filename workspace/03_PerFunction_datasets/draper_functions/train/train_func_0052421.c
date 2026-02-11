usbtv_audio_resume(struct usbtv *usbtv)
{
	if (atomic_read(&usbtv->snd_stream) && usbtv->snd_bulk_urb)
		usb_submit_urb(usbtv->snd_bulk_urb, GFP_ATOMIC);
}
