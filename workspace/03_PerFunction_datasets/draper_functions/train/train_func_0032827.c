initialize_F(void)
{
  register int i;
  register int j;
  register int k;
  register shifts *sp;
  register short *edge;
  register unsigned *rowp;
  register short *rp;
  register short **reads;
  register int nedges;
  register int stateno;
  register int symbol;
  register int nwords;

  nwords = ngotos * tokensetsize;
  F = NEW2(nwords, unsigned);

  reads = NEW2(ngotos, short *);
  edge = NEW2(ngotos + 1, short);
  nedges = 0;

  rowp = F;
  for (i = 0; i < ngotos; i++)
    {
      stateno = to_state[i];
      sp = shift_table[stateno];

      if (sp)
        {
          k = sp->nshifts;

          for (j = 0; j < k; j++)
            {
              symbol = accessing_symbol[sp->shift[j]];
              if (ISVAR(symbol))
                break;
              SETBIT(rowp, symbol);
            }

          for (; j < k; j++)
            {
              symbol = accessing_symbol[sp->shift[j]];
              if (nullable[symbol])
                edge[nedges++] = map_goto(stateno, symbol);
            }

          if (nedges)
            {
              reads[i] = rp = NEW2(nedges + 1, short);

              for (j = 0; j < nedges; j++)
                rp[j] = edge[j];

              rp[nedges] = -1;
              nedges = 0;
            }
        }

      rowp += tokensetsize;
    }

  SETBIT(F, 0);
  digraph(reads);

  for (i = 0; i < ngotos; i++)
    {
      if (reads[i])
        FREE(reads[i]);
    }

  FREE(reads);
  FREE(edge);
}
