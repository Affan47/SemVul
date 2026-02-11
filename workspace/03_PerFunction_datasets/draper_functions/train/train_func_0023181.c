interrupt_gen(int scanline)
{

	cpu_set_irq_line(0, 0, (scanline & 32) ? ASSERT_LINE : CLEAR_LINE);


	scanline += 32;
	if (scanline >= 256)
		scanline -= 256;
	timer_set(cpu_getscanlinetime(scanline), scanline, interrupt_gen);
}
