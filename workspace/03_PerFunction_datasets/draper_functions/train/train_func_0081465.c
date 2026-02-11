yunsung8_adpcm_int(int irq)
{
	static int toggle=0;

	MSM5205_data_w (0,adpcm>>4);
	adpcm<<=4;

	toggle ^= 1;
	if (toggle)
		cpu_set_nmi_line(1,PULSE_LINE);
}
