SetVoiceByName(const char *name)
{
	espeak_VOICE *v;
	espeak_VOICE voice_selector;
	char *variant_name;
	static char buf[60];

	strncpy0(buf,name,sizeof(buf));
	variant_name = ExtractVoiceVariantName(buf, 0, 1);

	memset(&voice_selector,0,sizeof(voice_selector));

	voice_selector.name = (char *)name;


	if(LoadVoice(buf,1) != NULL)
	{
		if(variant_name[0] != 0)
		{
			LoadVoice(variant_name,2);
		}

		DoVoiceChange(voice);
		SetVoiceStack(&voice_selector, variant_name);
		return(EE_OK);
	}

	if(n_voices_list == 0)
		espeak_ListVoices(NULL);

	if((v = SelectVoiceByName(voices_list,buf)) != NULL)
	{
		if(LoadVoice(v->identifier,0) != NULL)
		{
			if(variant_name[0] != 0)
			{
				LoadVoice(variant_name,2);
			}
			DoVoiceChange(voice);
			SetVoiceStack(&voice_selector, variant_name);
			return(EE_OK);
		}
	}
	return(EE_INTERNAL_ERROR);
}
