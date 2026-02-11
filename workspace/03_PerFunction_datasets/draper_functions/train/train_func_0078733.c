attribute(Aword id, Aword atr)
#else
Aptr attribute(id, atr)
     Aword id, atr;
#endif
{
  char str[80];

  if (isObj(id))
    return objatr(id, atr);
  else if (isLoc(id))
    return locatr(id, atr);
  else if (isAct(id))
    return actatr(id, atr);
  else if (isLit(id))
    return litatr(id, atr);
  else {
    sprintf(str, "Can't ATTRIBUTE item (%ld).", (unsigned long) id);
    syserr(str);
  }
  return(EOF);
}
