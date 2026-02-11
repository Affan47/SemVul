snd_pcm_ioplug_mmap_commit(snd_pcm_t *pcm,
						    snd_pcm_uframes_t offset,
						    snd_pcm_uframes_t size)
{
	if (pcm->stream == SND_PCM_STREAM_PLAYBACK &&
	    pcm->access != SND_PCM_ACCESS_RW_INTERLEAVED &&
	    pcm->access != SND_PCM_ACCESS_RW_NONINTERLEAVED) {
		const snd_pcm_channel_area_t *areas;
		snd_pcm_uframes_t ofs, frames = size;

		snd_pcm_mmap_begin(pcm, &areas, &ofs, &frames);
		if (ofs != offset)
			return -EIO;
		return ioplug_priv_transfer_areas(pcm, areas, offset, frames);
	}

	snd_pcm_mmap_appl_forward(pcm, size);
	return size;
}
