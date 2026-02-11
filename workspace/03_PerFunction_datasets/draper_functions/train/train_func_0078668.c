sh2_timer_callback(int cpunum)
{
	UINT16 frc;

	cpuintrf_push_context(cpunum);
	sh2_timer_resync();

	frc = sh2.frc;

	if(frc == sh2.ocrb)
		sh2.m[4] |= OCFB;

	if(frc == 0x0000)
		sh2.m[4] |= OVF;

	if(frc == sh2.ocra)
	{
		sh2.m[4] |= OCFA;

		if(sh2.m[4] & 0x010000)
			sh2.frc = 0;
	}

	sh2_recalc_irq();
	sh2_timer_activate();

	cpuintrf_pop_context();
}
