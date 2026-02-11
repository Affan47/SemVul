ChangeWordStress(Translator *tr, char *word, int new_stress)
{
	int ix;
	unsigned char *p;
	int  max_stress;
	int  vowel_count;
	int  stressed_syllable=0;
	unsigned char phonetic[N_WORD_PHONEMES];
	signed char vowel_stress[N_WORD_PHONEMES/2];

	strcpy((char *)phonetic,word);
	max_stress = GetVowelStress(tr, phonetic, vowel_stress, vowel_count, stressed_syllable, 0);

	if(new_stress >= 4)
	{

		for(ix=1; ix<vowel_count; ix++)
		{
			if(vowel_stress[ix] >= max_stress)
			{
				vowel_stress[ix] = new_stress;
				break;
			}
		}
	}
	else
	{

		for(ix=1; ix<vowel_count; ix++)
		{
			if(vowel_stress[ix] > new_stress)
				vowel_stress[ix] = new_stress;
		}
	}


	ix = 1;
	p = phonetic;
	while(*p != 0)
	{
		if((phoneme_tab[*p]->type == phVOWEL) && !(phoneme_tab[*p]->phflags & phNONSYLLABIC))
		{
			if((vowel_stress[ix] == 0) || (vowel_stress[ix] > 1))
				*word++ = stress_phonemes[(unsigned char)vowel_stress[ix]];

			ix++;
		}
		*word++ = *p++;
	}
	*word = 0;
}
