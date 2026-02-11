sync_slave_read(snd_pcm_t *pcm)
{
	mmap_emul_t *map = pcm->private_data;
	snd_pcm_t *slave = map->gen.slave;
	snd_pcm_uframes_t offset;
	snd_pcm_sframes_t size;

	size = *slave->hw.ptr - map->hw_ptr;
	if (size < 0)
		size += pcm->boundary;
	if (!size)
		return 0;
	offset = map->hw_ptr % pcm->buffer_size;
	size = snd_pcm_read_mmap(pcm, offset, size);
	if (size > 0)
		snd_pcm_mmap_hw_forward(pcm, size);
	return 0;
}
