print_flags(uint8_t mask, uint8_t cmp, int invert, int numeric)
{
	if (mask || invert) {
		printf("flags:%s", invert ? "!" : "");
		if (numeric)
			printf(" 0x%02X/0x%02X", mask, cmp);
		else {
			printf(" ");
			print_tcpf(mask);
			printf("/");
			print_tcpf(cmp);
		}
	}
}
