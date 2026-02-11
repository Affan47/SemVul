snd_via686_playback_open(struct snd_pcm_substream *substream)
{
	struct via82xx *chip = snd_pcm_substream_chip(substream);
	struct viadev *viadev = &chip->devs[chip->playback_devno + substream->number];
	int err;

	if ((err = snd_via82xx_pcm_open(chip, viadev, substream)) < 0)
		return err;
	return 0;
}
