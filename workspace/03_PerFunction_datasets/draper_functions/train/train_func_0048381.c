MSM5205_sh_reset(void)
{
	int i;


	if (Machine->sample_rate == 0)
		return;

	for (i = 0; i < msm5205_intf->num; i++)
	{
		struct MSM5205Voice *voice = &msm5205[i];

		voice->data    = 0;
		voice->vclk    = 0;
		voice->reset   = 0;
		voice->signal  = 0;
		voice->step    = 0;

		MSM5205_playmode_w(i,msm5205_intf->select[i]);
	}
}
