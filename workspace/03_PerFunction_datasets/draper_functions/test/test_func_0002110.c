midi_note_name (uint8_t val)
{
	if (val > 127) {
		return "???";
	}

	static const char* notes[] = {
		"C",
		"C#",
		"D",
		"D#",
		"E",
		"F",
		"F#",
		"G",
		"G#",
		"A",
		"A#",
		"B"
	};


	int octave = val / 12 - 1;
	static char buf[8];

	val = val % 12;

	snprintf (buf, sizeof (buf), "%s%d", notes[val], octave);
	return buf;
}

}
