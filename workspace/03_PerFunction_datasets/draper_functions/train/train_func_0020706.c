SynthOnTimer()
{
	if(!timer_on)
	{
		return(WavegenCloseSound());
	}

	do {
		if(WcmdqUsed() > 0)
			WavegenOpenSound();

		if(Generate(phoneme_list,&n_phoneme_list,1)==0)
		{
			SpeakNextClause(NULL,NULL,1);
		}
	} while(skipping_text);

	return(0);
}
