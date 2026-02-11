PrintSigns()
{
  byte sz[cchSzDef];
  int i;

  sprintf(sz, "%s signs and houses:\n", szAppName); PrintSz(sz);
  PrintSz("Sign        English name      House Traditional name");
  PrintTab(' ', 19); PrintSz("Ruler\n\n");
  for (i = 1; i <= cSign; i++) {
    AnsiColor(kSignA(i));
    sprintf(sz, "%-12sthe %-14s%2d%s  House of %-24s  %s\n",
    szSignName[i], szSignEnglish[i], i, szSuffix[i], szHouseTradition[i],
    szObjName[rules[i]]);
    PrintSz(sz);
  }
  AnsiColor(kDefault);
}
