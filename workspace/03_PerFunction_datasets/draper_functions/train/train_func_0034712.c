alpha_row_update(int scanline)
{
	data16_t *check = &atarigen_alpha[(scanline / 8) * 64 + 42];


	if (check < &atarigen_alpha[0x7c0] && (*check & 0x8000))
		timer_set(cpu_getscanlineperiod() * 6.9, 0, irq_gen);


	skullxbo_scanline_update(scanline);
}
