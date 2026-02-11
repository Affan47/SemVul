FindPhonemesUsed(void)
{
	int hash;
	char *p;
	unsigned int *pw;
	char *next;
	unsigned char c;
	int count = 0;
	int ignore;
	char phonetic[N_WORD_PHONEMES];


	p = translator->data_dictrules;
	while(*p != 0)
	{
		if(*p == RULE_CONDITION)
			p+=2;
		if(*p == RULE_LINENUM)
			p+=3;
		if(*p == RULE_GROUP_END)
		{
			p++;
			if(*p == 0) break;
		}
		if(*p == RULE_GROUP_START)
		{
			if(p[1] == RULE_REPLACEMENTS)
			{
				p++;
				pw = (unsigned int *)(((long)p+4) & ~3);
				while(pw[0] != 0)
				{
					pw += 2;
				}
				p = (char *)(pw+1);
				continue;
			}

			if(p[1] == RULE_LETTERGP2)
			{
				while(*p != RULE_GROUP_END) p++;
				continue;
			}

			p += (strlen(p)+1);
		}

		while((c = *p) != 0)
		{
			if(c == RULE_CONDITION)
				p++;
			if(c == RULE_PHONEMES)
				break;
			p++;
		}


		count++;
		if(c == RULE_PHONEMES)
		{
			ignore = 0;
			p++;
			while((c = *p) != 0)
			{
				if(c == phonSWITCH)
					ignore = 1;

				if(ignore == 0)
					phoneme_tab_flags[c] |= 2;
				p++;
			}
		}
		p++;
	}


	for(hash=0; hash<N_HASH_DICT; hash++)
	{
		p = translator->dict_hashtab[hash];
		if(p == NULL)
			continue;

		while(*p != 0)
		{
			next = p + p[0];
			if((p[1] & 0x80) == 0)
			{
				p += ((p[1] & 0x3f) + 2);
				strcpy(phonetic,p);
				p += strlen(phonetic) +1;


				ignore = 0;
				while(p < next)
				{
					if(*p == BITNUM_FLAG_TEXTMODE)
					{
						ignore = 1;
						break;
					}
					p++;
				}

				if(ignore == 0)
				{
					p = phonetic;
					while((c = *p) != 0)
					{
						if(c == phonSWITCH)
							break;

						phoneme_tab_flags[c] |= 2;
						p++;
					}
				}
			}
			p = next;
		}
	}
}
