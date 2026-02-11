expand_suf_into_table (rootword, mask, optflags, exptable,
				   existing_flags)
    ichar_t *			rootword;
    register MASKTYPE		mask[];
    int				optflags;
    struct exp_table *          exptable;
    MASKTYPE                    existing_flags[];
    {
    int				entcount;
    register struct flagent *
				flent;

    for (flent = sflaglist, entcount = numsflags;
      entcount > 0;
      flent++, entcount--)
	{
	if (TSTMASKBIT (mask, flent->flagbit))
	    {
	    if ((optflags & FF_CROSSPRODUCT) == 0
	      ||  (flent->flagflags & FF_CROSSPRODUCT))
		(void) gen_suf_expansion (rootword, flent, exptable,
					  existing_flags);
	    }
	}
    }
