dotrees()
{

  long lastchar;
  ajint ival=0;

  charindex = 0;
  lastchar = 0;
  offset = 0;
  charnumber = 0;
  ajReadlineTrim(inputfile, &rdline);
  if(ajFmtScanS(rdline, "%d", &ival) != 1) {
    printf("Invalid input file!\n");
    embExitBad();
  }
  charnumber = ival;
  while (charnumber < 999) {
    if (charnumber < lastchar) {
      printf("\n\nERROR: Character state tree");
      printf(" for character %ld: out of order\n\n", charnumber);
      embExitBad();
    }
    charindex++;
    lastindex = charindex;
    readtree();
    if (npairs > 0) {
      construct();
      factortree();
    } else {
      nstates = 0;
      ancsymbol[charindex - 1] = '?';
    }
    lastchar = charnumber;
    charnum[charindex - 1] = charnumber;
    chstart[charindex - 1] = offset;
    numstates[charindex - 1] = nstates;
    offset += nstates * nstates;
    ajReadlineTrim(inputfile, &rdline);
    ajFmtScanS(rdline, "%d", &ival);
    charnumber = ival;
  }


}
