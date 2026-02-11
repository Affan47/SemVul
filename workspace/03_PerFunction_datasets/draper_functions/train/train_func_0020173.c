scs_input_packet(struct scs *scs,
			     struct snd_rawmidi_substream *stream,
			     const u8 *data, unsigned int bytes)
{
	unsigned int i;

	if (data[0] == HSS1394_TAG_USER_DATA) {
		for (i = 1; i < bytes; ++i)
			scs_input_midi_byte(scs, stream, data[i]);
	} else {
		snd_rawmidi_receive(stream, sysex_escape_prefix,
				    ARRAY_SIZE(sysex_escape_prefix));
		for (i = 0; i < bytes; ++i)
			scs_input_escaped_byte(stream, data[i]);
		snd_rawmidi_receive(stream, (const u8[]) { 0xf7 }, 1);
	}
}
