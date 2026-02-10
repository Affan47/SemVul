check_suggestions(su, gap)
    suginfo_T	*su;
    garray_T	*gap;
{
    suggest_T   *stp;
    int		i;
    char_u	longword[MAXWLEN + 1];
    int		len;
    hlf_T	attr;

    stp = &SUG(*gap, 0);
    for (i = gap->ga_len - 1; i >= 0; --i)
    {

	vim_strncpy(longword, stp[i].st_word, MAXWLEN);
	len = stp[i].st_wordlen;
	vim_strncpy(longword + len, su->su_badptr + stp[i].st_orglen,
							       MAXWLEN - len);
	attr = HLF_COUNT;
	(void)spell_check(curwin, longword, &attr, NULL, FALSE);
	if (attr != HLF_COUNT)
	{

	    vim_free(stp[i].st_word);
	    --gap->ga_len;
	    if (i < gap->ga_len)
		mch_memmove(stp + i, stp + i + 1,
				       sizeof(suggest_T) * (gap->ga_len - i));
	}
    }
}
