FillSymbolRing(symbol, factor)
real *symbol;
real factor;
{
  real orb = DEFORB*256.0/(real)gs.yWin*(real)gi.nScale*factor, k1, k2, temp;
  int i, j, k = 1, l;


  for (l = 0; k && l < us.nDivision*2; l++) {
    k = 0;
    for (i = 0; i <= cObj; i++) if (FProper(i)) {


      k1 = rLarge; k2 = -rLarge;
      for (j = 0; j <= cObj; j++)
        if (FProper(j) && i != j) {
          temp = symbol[j]-symbol[i];
          if (RAbs(temp) > rDegHalf)
            temp -= rDegMax*RSgn(temp);
          if (temp < k1 && temp > 0.0)
            k1 = temp;
          else if (temp > k2 && temp <= 0.0)
            k2 = temp;
        }


      if (k2 > -orb && k1 > orb) {
        k = 1; symbol[i] = Mod(symbol[i]+orb*0.51+k2*0.49);
      } else if (k1 < orb && k2 < -orb) {
        k = 1; symbol[i] = Mod(symbol[i]-orb*0.51+k1*0.49);


      } else if (k2 > -orb && k1 < orb) {
        k = 1; symbol[i] = Mod(symbol[i]+(k1+k2)*0.5);
      }
    }
  }
}
