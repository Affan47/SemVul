QRinput_estimateVersion(QRinput *input)
{
	int bits;
	int version, prev;

	version = 0;
	do {
		prev = version;
		bits = QRinput_estimateBitStreamSize(input, prev);
		version = QRspec_getMinimumVersion((bits + 7) / 8, input->level);
		if (version < 0) {
			return -1;
		}
	} while (version > prev);

	return version;
}
