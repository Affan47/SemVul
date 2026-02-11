snd_fm801_capture_pointer(struct snd_pcm_substream *substream)
{
	struct fm801 *chip = snd_pcm_substream_chip(substream);
	size_t ptr;

	if (!(chip->cap_ctrl & FM801_START))
		return 0;
	spin_lock(&chip->reg_lock);
	ptr = chip->cap_pos + (chip->cap_count - 1) - fm801_readw(chip, CAP_COUNT);
	if (fm801_readw(chip, IRQ_STATUS) & FM801_IRQ_CAPTURE) {
		ptr += chip->cap_count;
		ptr %= chip->cap_size;
	}
	spin_unlock(&chip->reg_lock);
	return bytes_to_frames(substream->runtime, ptr);
}
