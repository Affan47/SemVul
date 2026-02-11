getIntelPNS(void)
{
	int i,j;
	long psn_eax, psn_ebx, psn_ecx, psn_edx;
	long char_hex;
	long ocpuid = 0x80000002;

	for(j = 0; j < 4; j++)
	{

		asm __volatile__(
			"pushl %%ebx\n\t" \
			"cpuid\n\t" \
			"movl %%ebx, %1\n\t" \
			"popl %%ebx\n\t" \
			: "=a" (psn_eax), "=r" (psn_ebx), "=c" (psn_ecx), "=d" (psn_edx)
			: "a" (ocpuid)
			: "cc"
		);


		for(i = 0; i < 4; i++)
		{
			char_hex = (psn_eax >> (i*8)) & 0xff;
			cprint(LINE_CPU+5, col + i, convert_hex_to_char(char_hex));

			char_hex = (psn_ebx >> (i*8)) & 0xff;
			cprint(LINE_CPU+5, col + i + 4, convert_hex_to_char(char_hex));

			if(psn_ecx != 0x20202020)
			{
				char_hex = (psn_ecx >> (i*8)) & 0xff;
				cprint(LINE_CPU+5, col + i + 8, convert_hex_to_char(char_hex));

				char_hex = (psn_edx >> (i*8)) & 0xff;
				cprint(LINE_CPU+5, col + i + 12, convert_hex_to_char(char_hex));
			}
			else
			{
				char_hex = (psn_edx >> (i*8)) & 0xff;
				cprint(LINE_CPU+5, col + i + 8, convert_hex_to_char(char_hex));
			}
		}
		(psn_ecx != 0x20202020)?(col += 16):(col +=12);
		if(psn_edx == 0x20202020) { col -= 4; }
		ocpuid++;
	}

	col -= 16;
}
