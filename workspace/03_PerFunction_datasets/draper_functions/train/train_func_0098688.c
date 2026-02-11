prtcode(int *codes)
{
	struct parse_event *p;

	for (p = key_events; p->name != NULL; p++) {
		if (p->value == (unsigned)codes[1]) {
			printf("scancode 0x%04x = %s (0x%02x)\n", codes[0], p->name, codes[1]);
			return;
		}
	}

	if (isprint (codes[1]))
		printf("scancode 0x%04x = '%c' (0x%02x)\n", codes[0], codes[1], codes[1]);
	else
		printf("scancode 0x%04x = 0x%02x\n", codes[0], codes[1]);
}
