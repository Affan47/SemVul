snd_mixer_oss_get_volume(struct snd_mixer_oss_file *fmixer, int slot)
{
	struct snd_mixer_oss *mixer = fmixer->mixer;
	struct snd_mixer_oss_slot *pslot;
	int result = 0, left, right;

	if (mixer == NULL || slot > 30)
		return -EIO;
	pslot = &mixer->slots[slot];
	left = pslot->volume[0];
	right = pslot->volume[1];
	if (pslot->get_volume)
		result = pslot->get_volume(fmixer, pslot, &left, &right);
	if (!pslot->stereo)
		right = left;
	if (snd_BUG_ON(left < 0 || left > 100))
		return -EIO;
	if (snd_BUG_ON(right < 0 || right > 100))
		return -EIO;
	if (result >= 0) {
		pslot->volume[0] = left;
		pslot->volume[1] = right;
	 	result = (left & 0xff) | ((right & 0xff) << 8);
	}
	return result;
}
