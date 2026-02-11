ins_root_cap (ichar_t *word, ichar_t *pattern,
				 int prestrip, int preadd, int sufstrip, int sufadd,
  				 struct dent *firstdent, struct flagent *pfxent, struct flagent *sufent)
{
    int			i;
    ichar_t		savearea[MAX_CAPS][INPUTWORDLEN + MAXAFFIXLEN];
    int			nsaved;

    nsaved = 0;
    save_root_cap (word, pattern, prestrip, preadd, sufstrip, sufadd,
      firstdent, pfxent, sufent, savearea, &nsaved);
    for (i = 0;  i < nsaved;  i++)
	{
		if (insert (savearea[i]) < 0)
			return -1;
	}
    return 0;
}
