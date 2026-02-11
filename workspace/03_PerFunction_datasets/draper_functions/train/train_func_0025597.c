multi_random_chat_start()
{
	int index;

	index = rand() % NUM_CHAT_START_WORDS;
	switch (index) {
		case 0:
			return XSTR("says",893);
		case 1:
			return XSTR("bleats",894);
		case 2:
			return XSTR("opines",895);
		case 3:
			return XSTR("postulates",896);
		case 4:
			return XSTR("declares",897);
		case 5:
			return XSTR("vomits out",898);
		case 6:
			return XSTR("whines",899);
		case 7:
			return XSTR("barks",900);
	}

	return NOX("Error");
}
