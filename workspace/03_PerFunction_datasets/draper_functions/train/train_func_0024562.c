dfaparse (char const *s, size_t len, struct dfa *d)
{
  dfa = d;
  lexptr = s;
  lexleft = len;
  lasttok = END;
  laststart = 1;
  parens = 0;
  if (MB_CUR_MAX > 1)
    {
      cur_mb_len = 0;
      memset(&mbs, 0, sizeof mbs);
    }

  if (! syntax_bits_set)
    dfaerror(_("no syntax specified"));

  tok = lex();
  depth = d->depth;

  regexp();

  if (tok != END)
    dfaerror(_("unbalanced )"));

  addtok(END - d->nregexps);
  addtok(CAT);

  if (d->nregexps)
    addtok(OR);

  ++d->nregexps;
}
