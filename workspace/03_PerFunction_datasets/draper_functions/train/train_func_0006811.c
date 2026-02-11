esl_msafile_selex_SetInmap(ESLX_MSAFILE *afp)
{
  int sym;

#ifdef eslAUGMENT_ALPHABET
  if (afp->abc)
    {
      for (sym = 0; sym < 128; sym++)
	afp->inmap[sym] = afp->abc->inmap[sym];
      afp->inmap[0]   = esl_abc_XGetUnknown(afp->abc);
      afp->inmap[' '] = esl_abc_XGetGap(afp->abc);
    }
#endif
  if (! afp->abc)
    {
      for (sym = 1; sym < 128; sym++)
	afp->inmap[sym] = (isgraph(sym) ? sym : eslDSQ_ILLEGAL);
      afp->inmap[0]   = '?';
      afp->inmap[' '] = '.';
    }
  return eslOK;
}
