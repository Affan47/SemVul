snd_p16v_pcm_pointer_playback(struct snd_pcm_substream *substream)
{
	struct snd_emu10k1 *emu = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_emu10k1_pcm *epcm = runtime->private_data;
	snd_pcm_uframes_t ptr, ptr1, ptr2,ptr3,ptr4 = 0;
	int channel = substream->pcm->device - emu->p16v_device_offset;
	if (!epcm->running)
		return 0;

	ptr3 = snd_emu10k1_ptr20_read(emu, PLAYBACK_LIST_PTR, channel);
	ptr1 = snd_emu10k1_ptr20_read(emu, PLAYBACK_POINTER, channel);
	ptr4 = snd_emu10k1_ptr20_read(emu, PLAYBACK_LIST_PTR, channel);
	if (ptr3 != ptr4) ptr1 = snd_emu10k1_ptr20_read(emu, PLAYBACK_POINTER, channel);
	ptr2 = bytes_to_frames(runtime, ptr1);
	ptr2+= (ptr4 >> 3) * runtime->period_size;
	ptr=ptr2;
        if (ptr >= runtime->buffer_size)
		ptr -= runtime->buffer_size;

	return ptr;
}
