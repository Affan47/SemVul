snd_ali_codec_read(struct snd_ac97 *ac97,
					 unsigned short reg)
{
	struct snd_ali *codec = ac97->private_data;

	dev_dbg(codec->card->dev, "codec_read reg=%xh.\n", reg);
	return snd_ali_codec_peek(codec, ac97->num, reg);
}
