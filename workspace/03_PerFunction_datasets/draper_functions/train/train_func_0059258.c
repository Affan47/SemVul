PrintWheelCenter(irow)
int irow;
{
  byte sz[cchSzDef], szT[8];
  int cch, nT;

  if (*ciMain.nam == chNull && *ciMain.loc == chNull)
    irow--;
  if (*ciMain.nam == chNull && irow >= 1)
    irow++;
  if (*ciMain.loc == chNull && irow >= 3)
    irow++;
  switch (irow) {
  case 0:
    sprintf(sz, "%s %s chart", szAppName, szVersionCore);
    break;
  case 1:
    sprintf(sz, "%s", ciMain.nam);
    break;
  case 2:
    nT = DayOfWeek(Mon, Day, Yea);
    sprintf(sz, "%c%c%c %s %s", chDay3(nT), SzDate(Mon, Day, Yea, 2),
      SzTim(Tim));
    break;
  case 3:
    sprintf(sz, "%s", ciMain.loc);
    break;
  case 4:
    nT = (int)(RFract(RAbs(Zon))*100.0+rRound);
    sprintf(sz, "%cT %c%02d:%02d, %s", ChDst(Dst),
      Zon > 0.0 ? '-' : '+', (int)RAbs(Zon), nT, SzLocation(Lon, Lat));
    break;
  case 5:
    nT = us.fEuroTime; us.fEuroTime = fTrue;
    sprintf(szT, "%s", SzTim(DegToDec(DFromR(is.RA)*(24.0/rDegMax))));
    sprintf(sz, "UT: %s, Sid.T: %s", SzTim(Tim+Zon-Dst), szT);
    us.fEuroTime = nT;
    break;
  case 6:
    sprintf(sz, "%s Houses", szSystem[us.nHouseSystem]);
    break;
  case 7:
    sprintf(sz, "%s / %s", us.fSidereal ? "Sidereal" : "Tropical",
      us.objCenter == oSun ? "Heliocentric" :
      (us.objCenter == oEar ? "Geocentric" : szObjName[us.objCenter]));
    break;
  case 8:
    sprintf(sz, "Julian Day = %12.4f", JulianDayFromTime(is.T));
    break;
  default:
    *sz = chNull;
  }
  cch = CchSz(sz);
  nT = WHEELCOLS*2-1 + is.fSeconds*8;
  PrintTab(' ', (nT - cch) / 2);
  PrintSz(sz);
  PrintTab(' ', nT-cch - (nT - cch) / 2);
}
