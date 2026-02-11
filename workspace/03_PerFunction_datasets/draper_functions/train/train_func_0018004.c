find_subweb (web, reg)
     struct web *web;
     rtx reg;
{
  struct web *w;
  if (GET_CODE (reg) != SUBREG)
    abort ();
  for (w = web->subreg_next; w; w = w->subreg_next)
    if (GET_MODE (w->orig_x) == GET_MODE (reg)
	&& SUBREG_BYTE (w->orig_x) == SUBREG_BYTE (reg))
      return w;
  return NULL;
}
