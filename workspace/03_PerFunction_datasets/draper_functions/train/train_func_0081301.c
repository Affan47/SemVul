master_reverb(float rvb)
{
	int master_rvb = (int)(rvb * 65536.0);
	audio_bus_controlf(7, 0, ABC_SEND_MASTER, 0.0);
	audio_bus_control(7, 1, ABC_SEND_MASTER, master_rvb);
	if(master_rvb)
		audio_bus_control(7, 1, ABC_FX_TYPE, AFX_REVERB);
	else
		audio_bus_control(7, 1, ABC_FX_TYPE, AFX_NONE);
}
