cpu_vblankreset(void)
{
	int cpunum;


	hs_update();


	update_input_ports();


	for (cpunum = 0; cpunum < cpu_gettotalcpu(); cpunum++)
	{
		if (!(cpu[cpunum].suspend & SUSPEND_REASON_DISABLE))
			cpu[cpunum].iloops = Machine->drv->cpu[cpunum].vblank_interrupts_per_frame - 1;
		else
			cpu[cpunum].iloops = -1;
	}
}
