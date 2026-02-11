ascii_to_raw(char a) {

	const unsigned char raw_to_ascii[] =
        "\000\0331234567890-=\177\t"
        "qwertyuiop[]\r\000as"
        "dfghjkl;'`\000\\zxcv"
        "bnm,./\000*\000 \000\201\202\203\204\205"
        "\206\207\210\211\212\000\000789-456+1"
        "230\177\000\000\213\214\000\000\000\000\000\000\000\000\000\000"
        "\r\000/";
	static unsigned char ascii_to_raw[sizeof(raw_to_ascii)];
	static int ascii_to_raw_built = 0;

	if (!ascii_to_raw_built) {
		int i;
		memset(ascii_to_raw, 0, sizeof(ascii_to_raw));
		for (i = 0; i < sizeof(raw_to_ascii); i++)
			if (raw_to_ascii[i])
				ascii_to_raw[tolower(raw_to_ascii[i])] = i;
		ascii_to_raw_built = 1;
	}

	return ascii_to_raw[(int)a];
}
