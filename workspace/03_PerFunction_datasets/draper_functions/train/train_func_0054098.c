ps3remote_decode(char *buff, int size, unsigned int *value)
{
	static unsigned int lastkey = 0;
	static unsigned int lastmask = 0;
	unsigned int i, mask;
	int retval;
	guint8 key;

	if (size < 12) {
		error("Got a shorter packet! (size %i)\n", size);
		return KEY_RESERVED;
	}

	mask = (buff[2] << 16) + (buff[3] << 8) + buff[4];
	key = buff[5];


	for (i = 0; i < 24; i++) {
		if ((lastmask & (1 << i)) == (mask & (1 << i)))
			continue;
		if (ps3remote_bits[i] == 0)
			goto error;
		retval = ps3remote_keymap[ps3remote_bits[i]];
		if (mask & (1 << i))

			*value = 1;
		else

			*value = 0;

		goto out;
	}

	*value = buff[11];
	if (buff[11] == 1) {
		retval = ps3remote_keymap[key];
	} else
		retval = lastkey;

	if (retval == KEY_RESERVED)
		goto error;
	if (retval == KEY_MAX)
		return retval;

	lastkey = retval;

out:
	fflush(stdout);

	lastmask = mask;

	return retval;

error:
	error("ps3remote: unrecognized sequence [%#x][%#x][%#x][%#x] [%#x],"
			"last: [%#x][%#x][%#x][%#x]",
			buff[2], buff[3], buff[4], buff[5], buff[11],
				lastmask >> 16, lastmask >> 8 & 0xff,
						lastmask & 0xff, lastkey);
	return -1;
}
