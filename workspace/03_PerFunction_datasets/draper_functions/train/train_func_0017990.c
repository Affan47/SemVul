ProcessPlanet(ind, aber)
int ind;
real aber;
{
  real ang, rad;

  RecToPol(spacex[ind], spacey[ind], &ang, &rad);
  planet[ind] = Mod(DFromR(ang)  - aber + is.rSid);
  RecToPol(rad, spacez[ind], &ang, &rad);
  if (us.objCenter == oSun && ind == oSun)
    ang = 0.0;
  ang = DFromR(ang);
  while (ang > rDegQuad)
    ang -= rDegHalf;
  while (ang < -rDegQuad)
    ang += rDegHalf;
  planetalt[ind] = ang;
}
