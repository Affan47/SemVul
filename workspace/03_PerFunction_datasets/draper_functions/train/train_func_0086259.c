StateSav_SaveINT(const int *data, int num)
{
	if (!StateFile || nFileError != Z_OK)
		return;


	while (num > 0) {
		UBYTE signbit = 0;
		unsigned int temp;
		UBYTE byte;
		int temp0;

		temp0 = *data++;
		if (temp0 < 0) {
			temp0 = -temp0;
			signbit = 0x80;
		}
		temp = (unsigned int) temp0;

		byte = temp & 0xff;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		temp >>= 8;
		byte = temp & 0xff;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		temp >>= 8;
		byte = temp & 0xff;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		temp >>= 8;
		byte = (temp & 0x7f) | signbit;
		if (GZWRITE(StateFile, &byte, 1) == 0) {
			GetGZErrorText();
			break;
		}

		num--;
	}
}
