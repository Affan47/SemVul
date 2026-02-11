spell_soundfold(slang, inword, folded, res)
    slang_T	*slang;
    char_u	*inword;
    int		folded;
    char_u	*res;
{
    char_u	fword[MAXWLEN];
    char_u	*word;

    if (slang->sl_sofo)

	spell_soundfold_sofo(slang, inword, res);
    else
    {

	if (folded)
	    word = inword;
	else
	{
	    (void)spell_casefold(inword, (int)STRLEN(inword), fword, MAXWLEN);
	    word = fword;
	}

#ifdef FEAT_MBYTE
	if (has_mbyte)
	    spell_soundfold_wsal(slang, word, res);
	else
#endif
	    spell_soundfold_sal(slang, word, res);
    }
}
