usX2Y_hwdep_urb_play_prepare(struct snd_usX2Y_substream *subs,
					struct urb *urb)
{
	int count, counts, pack;
	struct usX2Ydev *usX2Y = subs->usX2Y;
	struct snd_usX2Y_hwdep_pcm_shm *shm = usX2Y->hwdep_pcm_shm;
	struct snd_pcm_runtime *runtime = subs->pcm_substream->runtime;

	if (0 > shm->playback_iso_start) {
		shm->playback_iso_start = shm->captured_iso_head -
			usX2Y_iso_frames_per_buffer(runtime, usX2Y);
		if (0 > shm->playback_iso_start)
			shm->playback_iso_start += ARRAY_SIZE(shm->captured_iso);
		shm->playback_iso_head = shm->playback_iso_start;
	}

	count = 0;
	for (pack = 0; pack < nr_of_packs(); pack++) {

		counts = shm->captured_iso[shm->playback_iso_head].length / usX2Y->stride;
		if (counts < 43 || counts > 50) {
			snd_printk(KERN_ERR "should not be here with counts=%i\n", counts);
			return -EPIPE;
		}

		urb->iso_frame_desc[pack].offset = shm->captured_iso[shm->playback_iso_head].offset;
		urb->iso_frame_desc[pack].length = shm->captured_iso[shm->playback_iso_head].length;
		if (atomic_read(&subs->state) != state_RUNNING)
			memset((char *)urb->transfer_buffer + urb->iso_frame_desc[pack].offset, 0,
			       urb->iso_frame_desc[pack].length);
		if (++shm->playback_iso_head >= ARRAY_SIZE(shm->captured_iso))
			shm->playback_iso_head = 0;
		count += counts;
	}
	urb->transfer_buffer_length = count * usX2Y->stride;
	return 0;
}
