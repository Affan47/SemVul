i_usX2Y_usbpcm_subs_startup(struct urb *urb)
{
	struct snd_usX2Y_substream *subs = urb->context;
	struct usX2Ydev *usX2Y = subs->usX2Y;
	struct snd_usX2Y_substream *prepare_subs = usX2Y->prepare_subs;
	if (NULL != prepare_subs &&
	    urb->start_frame == prepare_subs->urb[0]->start_frame) {
		atomic_inc(&prepare_subs->state);
		if (prepare_subs == usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE]) {
			struct snd_usX2Y_substream *cap_subs2 = usX2Y->subs[SNDRV_PCM_STREAM_CAPTURE + 2];
			if (cap_subs2 != NULL)
				atomic_inc(&cap_subs2->state);
		}
		usX2Y_usbpcm_subs_startup_finish(usX2Y);
		wake_up(&usX2Y->prepare_wait_queue);
	}

	i_usX2Y_usbpcm_urb_complete(urb);
}
