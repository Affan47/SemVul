HouseRegiomontanus()
{
  real D, X;
  int i;

  if (hRevers) {
    hRevers = 2;
    is.Asc = Mod(is.Asc -rDegHalf);
  }

  for (i = 1; i <= cSign; i++) {
    if(hRevers && !PolarMCflip)
      D = RFromD(300.0-30.0*(real)i);
    else
      D = RFromD(60.0+30.0*(real)i);
    X = Angle(RCos(is.RA+D)*RCos(is.OB)-RSin(D)*RTan(AA)*RSin(is.OB),
      RSin(is.RA+D));
    chouse[i] = Mod(DFromR(X)+is.rSid);
  }
  if (hRevers && PolarMCflip) {
    is.MC = Mod(is.MC -rDegHalf);
    for (i = 1; i <= cSign; i++)
      chouse[i] = Mod(chouse[i] - rDegHalf);
  }
}
