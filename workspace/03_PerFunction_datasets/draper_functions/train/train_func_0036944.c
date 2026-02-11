snd_uart16550_rmidi(struct snd_uart16550 *uart, int device,
			       int outs, int ins,
			       struct snd_rawmidi **rmidi)
{
	struct snd_rawmidi *rrawmidi;
	int err;

	err = snd_rawmidi_new(uart->card, "UART Serial MIDI", device,
			      outs, ins, &rrawmidi);
	if (err < 0)
		return err;
	snd_rawmidi_set_ops(rrawmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_uart16550_input);
	snd_rawmidi_set_ops(rrawmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_uart16550_output);
	strcpy(rrawmidi->name, "Serial MIDI");
	snd_uart16550_substreams(&rrawmidi->streams[SNDRV_RAWMIDI_STREAM_OUTPUT]);
	snd_uart16550_substreams(&rrawmidi->streams[SNDRV_RAWMIDI_STREAM_INPUT]);
	rrawmidi->info_flags = SNDRV_RAWMIDI_INFO_OUTPUT |
			       SNDRV_RAWMIDI_INFO_INPUT |
			       SNDRV_RAWMIDI_INFO_DUPLEX;
	rrawmidi->private_data = uart;
	if (rmidi)
		*rmidi = rrawmidi;
	return 0;
}
