interpret_standby(uint8_t standby)
{
	printf(" (");
	if (standby == 0) {
		printf("off");
	} else if (standby <= 240 || standby == 252 || standby == 255) {

		unsigned t = standby * 5;
		printf("%u minutes %u seconds", t / 60, t % 60);
	} else if (standby <= 251) {
		unsigned t = (standby - 240); ;
		printf("%u.%c hours", t / 2, (t & 1) ? '5' : '0');
	}
	if (standby == 253)
		printf("vendor-specific");
	if (standby == 254)
		printf("reserved");
	printf(")\n");
}
