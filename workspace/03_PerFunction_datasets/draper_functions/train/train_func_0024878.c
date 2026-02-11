adpcm_int(int data)
{
	static int toggle;

	MSM5205_data_w(0,msm5205next >> 4);
	msm5205next<<=4;

	toggle = 1 - toggle;
	if (toggle)
	{
		if (resetkludge)
		cpu_set_nmi_line(0,PULSE_LINE);
	}
}
