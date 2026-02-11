PrintGrand(ac, i1, i2, i3, i4)
byte ac;
int i1, i2, i3, i4;
{
  byte sz[cchSzDef];
  int asp;

  switch (ac) {
  case acS : asp = aCon; break;
  case acGT: asp = aTri; break;
  case acTS: asp = aOpp; break;
  case acY : asp = aInc; break;
  case acGC: asp = aSqu; break;
  case acC : asp = aSex; break;
  case acMR: asp = aSex; break;
  case acK : asp = aTri; break;
  default: ;
  }
  AnsiColor(kAspA[asp]);
  sprintf(sz, "%-11s", szAspectConfig[ac]); PrintSz(sz);
  AnsiColor(kDefault);
  sprintf(sz, " %s ", ac == acS || ac == acGT || ac == acGC ||
     ac == acMR || ac == acK ? "with" : "from"); PrintSz(sz);
  AnsiColor(kObjA[i1]);
  sprintf(sz, "%c%c%c: ", chObj3(i1)); PrintSz(sz);
  PrintZodiac(planet[i1]);
  sprintf(sz, " %s ", ac == acS || ac == acGT || ac == acK ? "and" : "to ");
  PrintSz(sz);
  AnsiColor(kObjA[i2]);
  sprintf(sz, "%c%c%c: ", chObj3(i2)); PrintSz(sz);
  PrintZodiac(planet[i2]);
  sprintf(sz, " %s ", ac == acGC || ac == acC || ac == acMR ? "to " : "and");
  PrintSz(sz);
  AnsiColor(kObjA[i3]);
  sprintf(sz, "%c%c%c: ", chObj3(i3)); PrintSz(sz);
  PrintZodiac(planet[i3]);
  if (ac == acGC || ac == acC || ac == acMR || ac == acK) {
    PrintSz(" to ");
    AnsiColor(kObjA[i4]);
    sprintf(sz, "%c%c%c: ", chObj3(i4)); PrintSz(sz);
    PrintZodiac(planet[i4]);
  }
  PrintL();
}
