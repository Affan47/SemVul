sh2_set_frt_input(int cpunum, int state)
{
	if(state == PULSE_LINE)
	{
		sh2_set_frt_input(cpunum, ASSERT_LINE);
		sh2_set_frt_input(cpunum, CLEAR_LINE);
		return;
	}

	cpuintrf_push_context(cpunum);

	if(sh2.frt_input == state) {
		cpuintrf_pop_context();
		return;
	}

	sh2.frt_input = state;

	if(sh2.m[5] & 0x8000) {
		if(state == CLEAR_LINE) {
			cpuintrf_pop_context();
			return;
		}
	} else {
		if(state == ASSERT_LINE) {
			cpuintrf_pop_context();
			return;
		}
	}

	sh2_timer_resync();
	sh2.icr = sh2.frc;
	sh2.m[4] |= ICF;
	logerror("SH2.%d: ICF activated (%x)\n", sh2.cpu_number, sh2.pc & AM);
	sh2_recalc_irq();
	cpuintrf_pop_context();
}
