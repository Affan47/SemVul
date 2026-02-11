ReservePhCodes()
{


	unsigned int word;
	MNEM_TAB *p;

	p = reserved_phonemes;
	while(p->mnem != NULL)
	{
		word = StringToWord(p->mnem);
		phoneme_tab2[p->value].mnemonic = word;
		phoneme_tab2[p->value].code = p->value;
		if(n_phcodes <= p->value)
			n_phcodes = p->value+1;
		p++;
	}
}
