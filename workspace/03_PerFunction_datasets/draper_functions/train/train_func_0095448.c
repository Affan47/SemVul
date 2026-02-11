csilver_adpcm_int(int data)
{
	static int toggle =0;

	toggle ^= 1;
	if (toggle)
		cpu_set_irq_line(2,M6502_IRQ_LINE,HOLD_LINE);

	MSM5205_data_w (0,msm5205next>>4);
	msm5205next<<=4;
}
