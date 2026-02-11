display_init(void)
{
	int i;
	volatile char *pp;

	serial_echo_init();
	serial_echo_print("\x1B[LINE_SCROLL;24r");
	serial_echo_print("\x1B[H\x1B[2J");
	serial_echo_print("\x1B[37m\x1B[44m");
	serial_echo_print("\x1B[0m");
	serial_echo_print("\x1B[37m\x1B[44m");


	for(i=0, pp=(char *)(SCREEN_ADR); i<80*24; i++) {
		*pp++ = ' ';
		*pp++ = 0x17;
	}


	for(i=0, pp=(char *)(SCREEN_ADR+1); i<TITLE_WIDTH; i++, pp+=2) {
		*pp = 0x20;
	}
	cprint(0, 0, "      Memtest86  v4.20      ");

	for(i=0, pp=(char *)(SCREEN_ADR+1); i<2; i++, pp+=30) {
		*pp = 0xA4;
	}
	cprint(0, 15, "+");


	for(i=0, pp=(char *)(SCREEN_ADR+1+(24 * 160)); i<80; i++, pp+=2) {
		*pp = 0x71;
	}

	serial_echo_print("\x1B[0m");
}
