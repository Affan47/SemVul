ReadParams()
{
	int ix, j;

	pitchenv.pitch1 = vd_pitch1->GetValue();
	pitchenv.pitch2 = vd_pitch2->GetValue();

	voice_data.pitch_base = (pitchenv.pitch1 - 9) << 12;
	voice_data.pitch_range = (pitchenv.pitch2 - pitchenv.pitch1) * 108;

	for(ix=0; ix<N_PEAKS+1; ix++)
	{
		for(j=0; j<3; j++)
		{
			voice_pcnt[ix][j] = vd[ix][j]->GetValue();
		}
	}
	VoiceSetup();

}
