dis_do_compare()
{
	word32	val1, val2;

	printf("Memory Compare from %02x/%04x.%04x with %02x/%04x\n", a1bank, a1, a2, g_a4bank, g_a4);
	while(a1 <= (a2 & 0xffff)) {
		val1 = get_memory_c((a1bank << 16) + a1, 0);
		val2 = get_memory_c((g_a4bank << 16) + g_a4, 0);
		if(val1 != val2) {
			printf("%02x/%04x: %02x vs %02x\n", a1bank, a1, val1, val2);
		}
		a1++;
		g_a4++;
	}
	a1 = a1 & 0xffff;
	g_a4 = g_a4 & 0xffff;
}
