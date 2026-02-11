LookupLetter2(Translator *tr, unsigned int letter, char *ph_buf)
{
	int len;
	char single_letter[10];

	single_letter[0] = 0;
	single_letter[1] = '_';
	len = utf8_out(letter, &single_letter[2]);
	single_letter[len+2] = ' ';
	single_letter[len+3] = 0;

	if(Lookup(tr, &single_letter[1], ph_buf) == 0)
	{
		single_letter[1] = ' ';
		if(Lookup(tr, &single_letter[2], ph_buf) == 0)
		{
			TranslateRules(tr, &single_letter[2], ph_buf, 20, NULL,0,NULL);
		}
	}
	return(ph_buf[0]);
}
