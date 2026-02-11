sysopen(afilename, aflags, mode)
  A	afilename;
  A	aflags;
  I	mode;
{
  char		*filename;
  unsigned long	flags;

  if ((filename = AToString(afilename)) == (char *)(-1) ||
      SymbolsToMask(OpenMasks, aflags, &flags)) {
    q = ERR_DOMAIN;
    R 0;
  } else
    R (I)open(filename, (int)flags, (int)mode);
}
