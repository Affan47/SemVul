mf_write_midi_event(struct MF *mf, unsigned long delta_time, unsigned int type, unsigned int chan, unsigned char *data, unsigned long size)
{
	int i;
	unsigned char c;

	WriteVarLen(mf, delta_time);


	c = type | chan;

	if (chan > 15)
		mferror(mf, "error: MIDI channel greater than 16\n");

	eputc(mf, c);


	for (i = 0; i < size; i++)
		eputc(mf, data[i]);

	return (size);
}
