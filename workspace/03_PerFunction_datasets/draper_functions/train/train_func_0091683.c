StateSav_ReadINT(int *data, int num)
{
	if (!StateFile || nFileError != Z_OK)
		return;

	while (num > 0) {
		UBYTE signbit = 0;
		int temp;
		UBYTE byte1, byte2, byte3, byte4;

		if (GZREAD(StateFile, &byte1, 1) == 0) {
			GetGZErrorText();
			break;
		}

		if (GZREAD(StateFile, &byte2, 1) == 0) {
			GetGZErrorText();
			break;
		}

		if (GZREAD(StateFile, &byte3, 1) == 0) {
			GetGZErrorText();
			break;
		}

		if (GZREAD(StateFile, &byte4, 1) == 0) {
			GetGZErrorText();
			break;
		}

		signbit = byte4 & 0x80;
		byte4 &= 0x7f;

		temp = (byte4 << 24) | (byte3 << 16) | (byte2 << 8) | byte1;
		if (signbit)
			temp = -temp;
		*data++ = temp;

		num--;
	}
}
