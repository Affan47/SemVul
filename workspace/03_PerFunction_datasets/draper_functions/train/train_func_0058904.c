hyprint(struct htrav_vars *Hyptrav, boolean *unknown,
                        bitptr dohyp, Char *guess)
{

  long i, j, k;
  char l;
  boolean dot, a0, a1, s0, s1;

  if (Hyptrav->bottom)
    fprintf(outfile, "root   ");
  else
    fprintf(outfile, "%3ld    ", Hyptrav->r->back->index - spp);
  if (Hyptrav->r->tip) {
    for (i = 0; i < nmlngth; i++)
      putc(nayme[Hyptrav->r->index - 1][i], outfile);
  } else
    fprintf(outfile, "%4ld      ", Hyptrav->r->index - spp);
  if (Hyptrav->nonzero)
    fprintf(outfile, "   yes    ");
  else if (*unknown)
    fprintf(outfile, "    ?     ");
  else
    fprintf(outfile, "   no     ");
  for (j = 1; j <= (chars); j++) {
    newline(outfile, j, 40, nmlngth + 17);
    k = (j - 1) / bits + 1;
    l = (j - 1) % bits + 1;
    dot = (((1L << l) & dohyp[k - 1]) == 0 && guess[j - 1] == '?');
    s0 = (((1L << l) & Hyptrav->r->statezero[k - 1]) != 0);
    s1 = (((1L << l) & Hyptrav->r->stateone[k - 1]) != 0);
    a0 = (((1L << l) & Hyptrav->zerobelow->bits_[k - 1]) != 0);
    a1 = (((1L << l) & Hyptrav->onebelow->bits_[k - 1]) != 0);
    dot = (dot || (a1 == s1 && a0 == s0));
    if (dot)
      putc('.', outfile);
    else {
      if (s0) {
        if (s1)
          putc('P', outfile);
        else
          putc('0', outfile);
      } else if (s1)
        putc('1', outfile);
      else
        putc('?', outfile);
    }
    if (j % 5 == 0)
      putc(' ', outfile);
  }
  putc('\n', outfile);
}
