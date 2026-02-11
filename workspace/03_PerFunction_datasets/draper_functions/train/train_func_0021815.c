LookupSpecial(Translator *tr, const char *string, char* text_out)
{
	unsigned int flags[2];
	char phonemes[55];
	char phonemes2[55];
	char *string1 = (char *)string;

	flags[0] = flags[1] = 0;
	if(LookupDictList(tr,&string1,phonemes,flags,0,NULL))
	{
		SetWordStress(tr, phonemes, flags, -1, 0);
		DecodePhonemes(phonemes,phonemes2);
		sprintf(text_out,"[\002%s]]",phonemes2);
		return(text_out);
	}
	return(NULL);
}
