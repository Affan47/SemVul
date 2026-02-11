bcd2000_midi_output_trigger(struct snd_rawmidi_substream *substream,
						int up)
{
	struct bcd2000 *bcd2k = substream->rmidi->private_data;

	if (up) {
		bcd2k->midi_out_substream = substream;

		if (!bcd2k->midi_out_active)
			bcd2000_midi_send(bcd2k);
	} else {
		bcd2k->midi_out_substream = NULL;
	}
}
