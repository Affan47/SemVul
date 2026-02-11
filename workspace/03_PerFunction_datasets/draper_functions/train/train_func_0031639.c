writePushString(char *str)
{
	unsigned int i;

	for (i = 0; i < nConstants; ++i) {
		if (strcmp(constants[i], str) == 0)
			break;
	}

	if (i < nConstants) {
		if (i < 256) {

			writeByte(0x08);
			writeByte((byte) i);
			return 2;
		}
		else {

			writeByte(0x09);
			writeShort(i);
			return 3;
		}
	}


	writeByte(0);
	return writeString(str) + 1;
}
