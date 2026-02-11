snd_virmidi_input_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct snd_virmidi *vmidi = substream->runtime->private_data;

	if (up) {
		vmidi->trigger = 1;
	} else {
		vmidi->trigger = 0;
	}
}
