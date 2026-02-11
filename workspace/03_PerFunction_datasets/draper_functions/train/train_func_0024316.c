midi_hexdump(byte *data, int size, int notational_offset)
{
	int offset = 0;
	int prev = 0;

	if (*data == 0xf0)
		offset = 8;

	while (offset < size) {
		int old_offset = offset;
		int offset_mod;
		int time = _parse_ticks(data + offset, &offset_mod,
					size);
		int cmd;
		int pleft;
		int firstarg;
		int i;
		int blanks = 0;

		offset += offset_mod;
		fprintf(stderr, "  [%04x] %d\t",
			old_offset + notational_offset, time);

		cmd = data[offset];
		if (!(cmd & 0x80)) {
			cmd = prev;
			if (prev < 0x80) {
				fprintf(stderr, "Track broken at %x after"
					" offset mod of %d\n",
					offset + notational_offset, offset_mod);
				sci_hexdump(data, size, notational_offset);
				return;
			}
			fprintf(stderr, "(rs %02x) ", cmd);
			blanks += 8;
		} else {
			++offset;
			fprintf(stderr, "%02x ", cmd);
			blanks += 3;
		}
		prev = cmd;

		pleft = MIDI_cmdlen[cmd >> 4];
		if (SCI_MIDI_CONTROLLER(cmd) && data[offset]
		    == SCI_MIDI_CUMULATIVE_CUE)
			--pleft;

		for (i = 0; i < pleft; i++) {
			if (i == 0)
				firstarg = data[offset];
			fprintf(stderr, "%02x ", data[offset++]);
			blanks += 3;
		}

		while (blanks < 16) {
			blanks += 4;
			fprintf(stderr, "    ");
		}

		while (blanks < 20) {
			++blanks;
			fprintf(stderr, " ");
		}

		if (cmd == SCI_MIDI_EOT)
			fprintf(stderr, ";; EOT");
		else if (cmd == SCI_MIDI_SET_SIGNAL) {
			if (firstarg == SCI_MIDI_SET_SIGNAL_LOOP)
				fprintf(stderr, ";; LOOP point");
			else
				fprintf(stderr, ";; CUE (%d)", firstarg);
		} else if (SCI_MIDI_CONTROLLER(cmd)) {
			if (firstarg == SCI_MIDI_CUMULATIVE_CUE)
				fprintf(stderr, ";; CUE (cumulative)");
			else if (firstarg == SCI_MIDI_RESET_ON_SUSPEND)
				fprintf(stderr, ";; RESET-ON-SUSPEND flag");
		}
		fprintf(stderr, "\n");

		if (old_offset >= offset) {
			fprintf(stderr, "-- Not moving forward anymore,"
				" aborting (%x/%x)\n", offset, old_offset);
			return;
		}
	}
}
