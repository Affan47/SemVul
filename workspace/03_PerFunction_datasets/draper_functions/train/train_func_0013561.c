FReadWorldData(nam, loc, lin)
byte FPTR **nam, FPTR **loc, FPTR **lin;
{
  static byte FPTR **psz = (byte FPTR **)szWorldData;
  int i;

  *loc = *psz++;
  *lin = *psz++;
  *nam = *psz++;
  if (*loc[0]) {
    if (gs.fPrintMap && gi.fFile) {
      i = **nam - '0';
      AnsiColor(i ? kRainbowA[i] : kMainA[7]);
      PrintSz(*nam+1); PrintL();
    }
    return fTrue;
  }
  psz = (byte FPTR **)szWorldData;
  return fFalse;
}
