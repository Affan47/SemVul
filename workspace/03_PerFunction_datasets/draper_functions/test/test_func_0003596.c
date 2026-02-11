snd_via82xx_codec_wait(struct snd_ac97 *ac97)
{
	struct via82xx *chip = ac97->private_data;
	int err;
	err = snd_via82xx_codec_ready(chip, ac97->num);

	if (!nodelay)
		msleep(500);
}
