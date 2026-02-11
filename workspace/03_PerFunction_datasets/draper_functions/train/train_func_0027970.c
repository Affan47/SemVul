extraletter (word)
    register ichar_t *	word;
    {
    ichar_t		newword[INPUTWORDLEN + MAXAFFIXLEN];
    register ichar_t *	p;
    register ichar_t *	r;

    if (icharlen (word) < 2)
	return;

    (void) icharcpy (newword, word + 1);
    for (p = word, r = newword;  *p != 0;  )
	{
	if (good (newword, 0, 1, 0, 0))
	    {
	    if (ins_cap (newword, word) < 0)
		return;
	    }
	*r++ = *p++;
	}
    }
