dec0_i8751_write(int data)
{

	if (GAME==1) hbarrel_i8751_write(data);
	if (GAME==2) baddudes_i8751_write(data);
	if (GAME==3) birdtry_i8751_write(data);

	cpu_set_irq_line(0,5,HOLD_LINE);


logerror("CPU #0 PC %06x: warning - write %02x to i8751\n",activecpu_get_pc(),data);

}
