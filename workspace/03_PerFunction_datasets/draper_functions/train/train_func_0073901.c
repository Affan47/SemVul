snd_ali_pointer(struct snd_pcm_substream *substream)
{
	struct snd_ali *codec = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_ali_voice *pvoice = runtime->private_data;
	unsigned int cso;

	spin_lock(&codec->reg_lock);
	if (!pvoice->running) {
		spin_unlock(&codec->reg_lock);
		return 0;
	}
	outb(pvoice->number, ALI_REG(codec, ALI_GC_CIR));
	cso = inw(ALI_REG(codec, ALI_CSO_ALPHA_FMS + 2));
	spin_unlock(&codec->reg_lock);

	cso %= runtime->buffer_size;
	return cso;
}
