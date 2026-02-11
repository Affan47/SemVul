set_goto_map()
{
  register shifts *sp;
  register int i;
  register int symbol;
  register int k;
  register Yshort *temp_map;
  register int state2;
  register int state1;

  goto_map = NEW2(nvars + 1, Yshort) - ntokens;
  temp_map = NEW2(nvars + 1, Yshort) - ntokens;

  ngotos = 0;
  for (sp = first_shift; sp; sp = sp->next)
    {
      for (i = sp->nshifts - 1; i >= 0; i--)
	{
	  symbol = accessing_symbol[sp->shift[i]];

	  if (ISTOKEN(symbol)) break;

	  if (ngotos == MAXSHORT)
	    fatal("too many gotos");

	  ngotos++;
	  goto_map[symbol]++;
        }
    }

  k = 0;
  for (i = ntokens; i < nsyms; i++)
    {
      temp_map[i] = k;
      k += goto_map[i];
    }

  for (i = ntokens; i < nsyms; i++)
    goto_map[i] = temp_map[i];

  goto_map[nsyms] = ngotos;
  temp_map[nsyms] = ngotos;

  from_state = NEW2(ngotos, Yshort);
  to_state = NEW2(ngotos, Yshort);

  for (sp = first_shift; sp; sp = sp->next)
    {
      state1 = sp->number;
      for (i = sp->nshifts - 1; i >= 0; i--)
	{
	  state2 = sp->shift[i];
	  symbol = accessing_symbol[state2];

	  if (ISTOKEN(symbol)) break;

	  k = temp_map[symbol]++;
	  from_state[k] = state1;
	  to_state[k] = state2;
	}
    }

  FREE(temp_map + ntokens);
}
