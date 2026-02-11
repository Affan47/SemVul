snd_vt1724_playback_indep_prepare(struct snd_pcm_substream *substream)
{
	struct snd_ice1712 *ice = snd_pcm_substream_chip(substream);
	unsigned char val;

	spin_lock_irq(&ice->reg_lock);
	val = 3 - substream->number;
	if (inb(ICEMT1724(ice, BURST)) < val)
		outb(val, ICEMT1724(ice, BURST));
	spin_unlock_irq(&ice->reg_lock);
	return snd_vt1724_pcm_prepare(substream);
}
